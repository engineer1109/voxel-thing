#include <iostream>
#include <stdexcept>
#include <cassert>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include <openvr.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <matrix.hpp>
#include <mesh.hpp>
#include <shader.hpp>
#include <texture.hpp>
#include <data.hpp>
#include <world.hpp>

#ifdef _WINDOWS
#   pragma comment(lib, "openvr_api")
#endif

const float nearClip = 0.1f;
const float farClip = 40.0f;

vr::IVRSystem *hmd;
GLFWwindow *window;

inline glm::mat4 toGlm(vr::HmdMatrix44_t& m) {
	glm::mat4 result = glm::mat4(
		m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0],
		m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1],
		m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2],
		m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3]);

  return result;
}

inline glm::mat4 toGlm(const vr::HmdMatrix34_t& m) {
  glm::mat4 result = glm::mat4(
      m.m[0][0], m.m[1][0], m.m[2][0], 0.0,
      m.m[0][1], m.m[1][1], m.m[2][1], 0.0,
      m.m[0][2], m.m[1][2], m.m[2][2], 0.0,
      m.m[0][3], m.m[1][3], m.m[2][3], 1.0f);

  return result;
}

inline vr::HmdMatrix34_t toOpenVR(const glm::mat4& m) {
  vr::HmdMatrix34_t result;
  for (uint8_t i = 0; i < 3; ++i) {
    for (uint8_t j = 0; j < 4; ++j) {
      result.m[i][j] = m[j][i];
    }
  }

  return result;
}

std::string getHMDString(vr::IVRSystem* pHmd, vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError* peError = nullptr) {
    uint32_t unRequiredBufferLen = pHmd->GetStringTrackedDeviceProperty(unDevice, prop, nullptr, 0, peError);
    if (unRequiredBufferLen == 0) {
        return "";
    }

    char* pchBuffer = new char[unRequiredBufferLen];
    unRequiredBufferLen = pHmd->GetStringTrackedDeviceProperty(unDevice, prop, pchBuffer, unRequiredBufferLen, peError);
    std::string sResult = pchBuffer;
    delete[] pchBuffer;

    return sResult;
}

vr::IVRSystem* initOpenVR(uint32_t& hmdWidth, uint32_t& hmdHeight) {
  vr::EVRInitError eError = vr::VRInitError_None;
  vr::IVRSystem* hmd = vr::VR_Init(&eError, vr::VRApplication_Scene);

  if (eError != vr::VRInitError_None) {
    fprintf(stderr, "OpenVR Initialization Error: %s\n", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
    return nullptr;
  }

  const std::string& driver = getHMDString(hmd, vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_TrackingSystemName_String);
  const std::string& model  = getHMDString(hmd, vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_ModelNumber_String);
  const std::string& serial = getHMDString(hmd, vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_SerialNumber_String);
  const float freq = hmd->GetFloatTrackedDeviceProperty(vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_DisplayFrequency_Float);

  //get the proper resolution of the hmd
  hmd->GetRecommendedRenderTargetSize(&hmdWidth, &hmdHeight);

  fprintf(stderr, "HMD: %s '%s' #%s (%d x %d @ %g Hz)\n", driver.c_str(), model.c_str(), serial.c_str(), hmdWidth, hmdHeight, freq);

  return hmd;
}

glm::mat4 currentViewProjectionMatrix(vr::Hmd_Eye nEye, vr::TrackedDevicePose_t* trackedDevicePose) {
  assert(trackedDevicePose[vr::k_unTrackedDeviceIndex_Hmd].bPoseIsValid);

  glm::mat4 proj = toGlm(hmd->GetProjectionMatrix(nEye, nearClip, farClip));
  glm::mat4 pos = glm::inverse(toGlm(hmd->GetEyeToHeadTransform(nEye)));
  glm::mat4 head = glm::inverse(toGlm(trackedDevicePose[vr::k_unTrackedDeviceIndex_Hmd].mDeviceToAbsoluteTracking));

  return proj * pos * head;
}

int main(void) {
  const int numEyes = 2;
  const vr::Hmd_Eye eyes[2] = { vr::Eye_Left, vr::Eye_Right };

  uint32_t framebufferWidth = 1280, framebufferHeight = 720;

  hmd = initOpenVR(framebufferWidth, framebufferHeight);
  if (!hmd) {
    return -1;
  }

  const int windowHeight = 720;
  const int windowWidth = (framebufferWidth * windowHeight) / framebufferHeight;

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  window = glfwCreateWindow(windowWidth, windowHeight, "openvr test", NULL, NULL);
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialise GLAD");
  }

  glfwSwapInterval(0);

  fprintf(stderr, "GPU: %s (OpenGL version %s)\n", glGetString(GL_RENDERER), glGetString(GL_VERSION));

  GLuint framebuffer[numEyes];
  glGenFramebuffers(numEyes, framebuffer);

  GLuint colorRenderTarget[numEyes];
  glGenTextures(numEyes, colorRenderTarget);
  GLuint depthRenderTarget[numEyes];
  glGenTextures(numEyes, depthRenderTarget);

  World world("data/world.json");

  for (int eye = 0; eye < numEyes; eye++) {
    glBindTexture(GL_TEXTURE_2D, colorRenderTarget[eye]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, framebufferWidth, framebufferHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glBindTexture(GL_TEXTURE_2D, depthRenderTarget[eye]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, framebufferWidth, framebufferHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer[eye]);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorRenderTarget[eye], 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthRenderTarget[eye], 0);
  }
  
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  Mesh cubeMesh(cube, { VEC3_VERTEX_ATTRIB, VEC3_VERTEX_ATTRIB });
  cubeMesh.bind();

  Shader worldShader("shaders/lighting.vert", "shaders/lighting.frag");
  Texture worldTexture("img/gray.jpeg");

  vr::TrackedDevicePose_t trackedDevicePose[vr::k_unMaxTrackedDeviceCount];

  glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(window)) {
    assert(glGetError() == GL_NONE);

    vr::VRCompositor()->WaitGetPoses(trackedDevicePose, vr::k_unMaxTrackedDeviceCount, nullptr, 0);

    for (int eye = 0; eye < numEyes; eye++) {
      glBindFramebuffer(GL_FRAMEBUFFER, framebuffer[eye]);
      glViewport(0, 0, framebufferWidth, framebufferHeight);

      glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      vr::Hmd_Eye vrEye = eyes[eye];
      glm::mat4 viewProjectionMatrix = currentViewProjectionMatrix(vrEye, trackedDevicePose);

      worldTexture.use();
      worldShader.use();

      worldShader.setVec3("lightColor", glm::vec3(1.0, 1.0, 1.0));
      worldShader.setVec3("lightPos", glm::vec3(0, 10, 0));
      worldShader.setVec3("viewPos", glm::vec3(0, 1, 0));

      for (int y = 0; y < WORLD_DEPTH; y++) {
        for (int x = 0; x < WORLD_WIDTH; x++) {
          std::shared_ptr<Chunk> chunk = world.chunks[y][x];

          glm::mat4 model;
          model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
          model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.5f));
          model = glm::translate(model, chunk->transform);

          glm::mat4 vpm = viewProjectionMatrix * model;

          worldShader.setMatrix("glob", glm::value_ptr(vpm));
          worldShader.setMatrix("model", glm::value_ptr(model));

          chunk->mesh->draw();
        }
      }

      const vr::Texture_t tex = { reinterpret_cast<void*>(intptr_t(colorRenderTarget[eye])), vr::TextureType_OpenGL, vr::ColorSpace_Gamma };

      vr::VRCompositor()->Submit(vr::EVREye(eye), &tex);
    }

    vr::VRCompositor()->PostPresentHandoff();

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, GL_NONE);
    glViewport(0, 0, windowWidth, windowHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlitFramebuffer(0, 0, framebufferWidth, framebufferHeight, 0, 0, windowWidth, windowHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, GL_NONE);

    // Display what has been drawn on the main window
    glfwSwapBuffers(window);

    glfwPollEvents();

    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
      glfwSetWindowShouldClose(window, 1);
    }
  }

  glfwTerminate();
  vr::VR_Shutdown();

  return 0;
}
