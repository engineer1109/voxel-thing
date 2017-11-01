#include <E/vr_context.hpp>

#include <iostream>

#include <openvr.h>

inline glm::mat4 toGlm(vr::HmdMatrix44_t m) {
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

void E::VRContext::init() {
  hmd = initOpenVR(framebufferWidth, framebufferHeight);

  glGenFramebuffers(numEyes, framebuffers);

  glGenTextures(numEyes, colorTargets);
  glGenTextures(numEyes, depthTargets);

  for (int i = 0; i < numEyes; i++) setupEye(i);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// called before state.update
void E::VRContext::preFrame() {
  vr::VRCompositor()->WaitGetPoses(trackedDevicePoses, vr::k_unMaxTrackedDeviceCount, nullptr, 0);
}

void E::VRContext::render(RenderManager *renderer) {
  for (int i = 0; i < numEyes; i++) {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[i]);
    glViewport(0, 0, framebufferWidth, framebufferHeight);

    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // TODO: preRender should only need to be called once per frame, but for some reason if it's outside of this loop we get all some weird shader related glitches.
    renderer->preRender();
    renderer->render(viewFor(eyes[i]));

    const vr::Texture_t tex = { reinterpret_cast<void*>(intptr_t(colorTargets[i])), vr::TextureType_OpenGL, vr::ColorSpace_Gamma };
    vr::VRCompositor()->Submit(vr::EVREye(i), &tex);
  }
}

// called after state.render
void E::VRContext::postFrame() {
  vr::VRCompositor()->PostPresentHandoff();
}

E::View E::VRContext::viewFor(vr::Hmd_Eye eye) {
  assert(trackedDevicePoses[vr::k_unTrackedDeviceIndex_Hmd].bPoseIsValid);

  glm::mat4 proj = toGlm(hmd->GetProjectionMatrix(eye, nearClip, farClip));
  glm::mat4 pos = glm::inverse(toGlm(hmd->GetEyeToHeadTransform(eye)));
  glm::mat4 head = glm::inverse(toGlm(trackedDevicePoses[vr::k_unTrackedDeviceIndex_Hmd].mDeviceToAbsoluteTracking));

  glm::mat4 viewProj = proj * pos * head;

  return View(viewProj);
}

void E::VRContext::setupEye(int eye) {
  // setup color render target
  glBindTexture(GL_TEXTURE_2D, colorTargets[eye]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, framebufferWidth, framebufferHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

  // setup depth render target
  glBindTexture(GL_TEXTURE_2D, depthTargets[eye]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, framebufferWidth, framebufferHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
 
  // put color and depth targets together on a framebuffer which represents the eye texture
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[eye]);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTargets[eye], 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTargets[eye], 0);
}

std::string E::VRContext::getHMDString(vr::IVRSystem* pHmd, vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError* peError) {
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

vr::IVRSystem* E::VRContext::initOpenVR(unsigned int &hmdWidth, unsigned int &hmdHeight) {
  vr::EVRInitError eError = vr::VRInitError_None;
  vr::IVRSystem* hmd = vr::VR_Init(&eError, vr::VRApplication_Scene);

  if (eError != vr::VRInitError_None) {
    printf("OpenVR Initialization Error: %s\n", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
    return NULL;
  }

  const std::string& driver = getHMDString(hmd, vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_TrackingSystemName_String);
  const std::string& model  = getHMDString(hmd, vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_ModelNumber_String);
  const std::string& serial = getHMDString(hmd, vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_SerialNumber_String);
  const float freq = hmd->GetFloatTrackedDeviceProperty(vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_DisplayFrequency_Float);

  //get the proper resolution of the hmd
  hmd->GetRecommendedRenderTargetSize(&hmdWidth, &hmdHeight);

  printf("HMD: %s '%s' #%s (%d x %d @ %g Hz)\n", driver.c_str(), model.c_str(), serial.c_str(), hmdWidth, hmdHeight, freq);

  return hmd;
}
