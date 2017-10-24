#include <application.hpp>

#include <iostream>

int main(void) {
  Application app;

  app.loop();

  return -1;
}

/*
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <array>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <camera.hpp>
#include <key_manager.hpp>
#include <shader.hpp>
#include <chunk.hpp>
#include <mesh.hpp>
#include <utils.hpp>
#include <data.hpp>
#include <texture.hpp>
#include <world.hpp>
#include <block.hpp>

KeyManager KEYS;

const float SCREEN_WIDTH=1600.0f;
const float SCREEN_HEIGHT=900.0f;

int frames = 0;

float lastTime;
float deltaTime;

bool debugMode = false;

Camera camera;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (action != GLFW_PRESS && action != GLFW_RELEASE) {
    return;
  }

  KEYS.set(key, action == GLFW_PRESS);
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

std::vector<float> rayLineVertData(glm::vec3 start, glm::vec3 end) {
  return {
    start.x, start.y, start.z, 1.0f, 1.0f, 1.0f,
    end.x, end.y, end.z, 1.0f, 1.0f, 1.0f
  };
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void mouseCallback(GLFWwindow *window, double x, double y) {
  camera.mouseCallback(x, y);
}

bool mouseButton = false;
bool lastMouseButton = false;
bool justClicked = false;

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mode) {
  lastMouseButton = mouseButton;

  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    mouseButton = true;
  } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
    mouseButton = false;
  }
}

int main(void) {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_FLOATING, GL_TRUE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "game", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();

    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cout << "Failed to initialise GLAD" << std::endl;

    return -1;
  }

  glEnable(GL_MULTISAMPLE);
  glEnable(GL_DEPTH_TEST);
  // glEnable(GL_CULL_FACE);

  // glCullFace(GL_BACK);  
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_WIDTH);

  // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glfwSetCursorPosCallback(window, mouseCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);

  Shader defaultShader("shaders/default.vert", "shaders/default.frag");
  Shader blockLightingShader("shaders/lighting.vert", "shaders/lighting.frag");
  Shader hudShader("shaders/hud.vert", "shaders/hud.frag");
  Shader posGizmoShader("shaders/pos_gizmo.vert", "shaders/pos_gizmo.frag");

  stbi_set_flip_vertically_on_load(true);

  Texture dirtTexture("img/ground.jpeg");
  Texture crosshairTexture("img/crosshair.jpg");

  Mesh crosshairMesh(quad, { VEC3_VERTEX_ATTRIB, VEC3_VERTEX_ATTRIB, VEC2_VERTEX_ATTRIB });
  crosshairMesh.bind();

  Mesh posGizmoMesh(xyzLines, { VEC3_VERTEX_ATTRIB, VEC3_VERTEX_ATTRIB }, GL_LINES);
  posGizmoMesh.bind();

  Mesh rayLineMesh(std::vector<float>(), { VEC3_VERTEX_ATTRIB, VEC3_VERTEX_ATTRIB }, GL_LINES);
  rayLineMesh.bind();

  Mesh lightMesh(cube, { VEC3_VERTEX_ATTRIB, VEC3_VERTEX_ATTRIB});
  lightMesh.bind();

  glm::vec3 lightPos(0, 2, 0);
  glm::vec3 lightColor(0.5, 0.2, 0.7);

  World world("world.json");

  // Setup ImGui binding
	ImGui_ImplGlfwGL3_Init(window, false);
  ImGui::SetMouseCursor(ImGuiMouseCursor_None);

  glfwSetKeyCallback(window, keyCallback);

  while (!glfwWindowShouldClose(window)) {
    deltaTime = (float) glfwGetTime() - lastTime;
    lastTime = (float) glfwGetTime();

    glfwPollEvents();
    KEYS.update();
    camera.update(deltaTime);

    if (KEYS.justDown(GLFW_KEY_F3)) {
      debugMode = !debugMode;
    }

    if (KEYS.justDown(GLFW_KEY_F4)) {
      world.save("world.json");
    }

    if (KEYS.down(GLFW_KEY_ESCAPE)) {
      glfwSetWindowShouldClose(window, true);
    }

    lightPos.x = sin(lastTime);
    lightPos.z = cos(lastTime);

    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.projectionMatrix();

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(95.0f), SCREEN_WIDTH/SCREEN_HEIGHT, 0.1f, 100.0f);

    blockLightingShader.use();

    blockLightingShader.setMatrix("view", glm::value_ptr(view));
    blockLightingShader.setMatrix("projection", glm::value_ptr(projection));

    blockLightingShader.setVec3("lightColor", lightColor);
    blockLightingShader.setVec3("lightPos", lightPos);
    blockLightingShader.setVec3("viewPos", camera.pos);

    dirtTexture.use();

    for (int y = 0; y < WORLD_DEPTH; y++) {
      for (int x = 0; x < WORLD_WIDTH; x++) {
        std::shared_ptr<Chunk> chunk = world.chunks[y][x];

        glm::mat4 model;
        model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.5f));
        model = glm::translate(model, chunk->transform);

        blockLightingShader.setMatrix("model", glm::value_ptr(model));

        chunk->mesh->draw();
      }
    }

    defaultShader.use();

    glm::mat4 model;
    model = glm::translate(model, lightPos);

    defaultShader.setMatrix("model", glm::value_ptr(model));
    defaultShader.setMatrix("view", glm::value_ptr(view));
    defaultShader.setMatrix("projection", glm::value_ptr(projection));

    lightMesh.draw();

    hudShader.use();

    model = glm::mat4();
    model = glm::scale(model, glm::vec3(0.005, 0.005, 0.005));

    hudShader.setMatrix("model", glm::value_ptr(model));
    crosshairTexture.use();
    crosshairMesh.draw();

    RayHit ray = world.ray(camera.pos, camera.front);

    if (ray.didHit && (!lastMouseButton && mouseButton)) {
      world.chunks[ray.chunk.z][ray.chunk.x]->data[ray.block.y][ray.block.z][ray.block.x] = SOLID;
      world.reloadChunks();

      mouseButton = false;

      rayLineMesh.updateData(rayLineVertData(ray.start, ray.end));
    }

    if (debugMode) {
      posGizmoShader.use();

      glm::mat4 model;
      model = glm::translate(model, glm::vec3(0, 0, 0));

      posGizmoShader.setMatrix("view", glm::value_ptr(view));
      posGizmoShader.setMatrix("projection", glm::value_ptr(projection));
      posGizmoShader.setMatrix("model", glm::value_ptr(model));

      posGizmoMesh.draw();

      rayLineMesh.draw();
    }

    ImGui_ImplGlfwGL3_NewFrame();

    if (debugMode) {
      ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 1.0f, 1.0f, 0.3f)); // Transparent background
      if (ImGui::Begin("Example: Fixed Overlay", &debugMode, ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_AlwaysAutoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoSavedSettings))
      {
        ImGui::Text("Voxel Bomber 0.0.1 [debug]");
        ImGui::Separator();

        ImGui::Columns(4, "mixed");

        ImGui::Text("Engine");
        ImGui::Indent(10.0f);
        ImGui::Text("fps: %f", frames / lastTime);
        ImGui::Text("time: %f", lastTime);
        ImGui::Text("delta: %f", deltaTime);
        ImGui::Unindent();
        ImGui::NextColumn();

        ImGui::Text("Camera");
        ImGui::Indent(10.0f);
        ImGui::Text("position: (%.1f,%.1f,%.1f)", camera.pos.x, camera.pos.y, camera.pos.z);
        ImGui::Text("rotation: (%.1f,%.1f,%.1f)", camera.front.x, camera.front.y, camera.front.z);
        ImGui::Unindent();
        ImGui::NextColumn();

        ImGui::Text("World");
        ImGui::Indent(10.0f);
        ImGui::Text("size: %d (%d,%d)", WORLD_WIDTH*WORLD_DEPTH, WORLD_WIDTH, WORLD_DEPTH);
        ImGui::Text("chunk size: (%d,%d,%d)", CHUNK_WIDTH, CHUNK_DEPTH, CHUNK_HEIGHT);
        ImGui::Unindent();
        ImGui::NextColumn();

        ImGui::Text("Ray");
        ImGui::Indent(10.0f);
        ImGui::Text("hit: %s", ray.didHit ? "true" : "false");
        if (ray.didHit) {
          ImGui::Text("chunk: (%d,%d,%d)", ray.chunk.x, ray.chunk.y, ray.chunk.z);
          ImGui::Text("block: (%d,%d,%d)", ray.block.x, ray.block.y, ray.block.z);
        }
        ImGui::Unindent();
        ImGui::NextColumn();

        ImGui::End();
      }
      ImGui::PopStyleColor();
    }

    ImGui::Render();

    glfwSwapBuffers(window);

    frames++;
  }

  ImGui_ImplGlfwGL3_Shutdown();
  glfwTerminate();

  return 0;
}
*/
