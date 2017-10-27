#include <application.hpp>

#include <stdexcept>
#include <iostream>

#include <glad/glad.h>
#include <stb_image.h>
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

#include <config.hpp>
#include <input.hpp>
#include <editor_state.hpp>

Application::Application() {
  Config *config = Config::instance();

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(config->screenWidth, config->screenHeight, "game", NULL, NULL);

  if (window == NULL) {
    glfwTerminate();

    throw std::runtime_error("Failed to create GLFW window");
  }

  glfwMakeContextCurrent(window);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialise GLAD");
  }

  glEnable(GL_DEPTH_TEST);

  glViewport(0, 0, config->screenWidth, config->screenHeight);

  stbi_set_flip_vertically_on_load(true);

  Input* input = Input::instance();

  glfwSetKeyCallback(window, Input::keyCallback);
  glfwSetMouseButtonCallback(window, Input::mouseButtonCallback);
  glfwSetCursorPosCallback(window, Input::mouseMovementCallback);
  glfwSetCursorPosCallback(window, Input::mouseMovementCallback);
  glfwSetScrollCallback(window, Input::mouseScrollCallback);

  ImGui_ImplGlfwGL3_Init(window, false);
  ImGuiIO& io = ImGui::GetIO();
  io.MouseDrawCursor = true;

  state = new EditorState(config, input);
  state->start();
}

void Application::loop() {
  while (!glfwWindowShouldClose(window)) {
    float deltaTime = (float) glfwGetTime() - lastTime;
    lastTime = (float) glfwGetTime();

    glfwPollEvents();
    ImGui_ImplGlfwGL3_NewFrame();

    Input *input = Input::instance();

    input->update();

    if (input->keys->justDown(GLFW_KEY_ESCAPE)) {
      glfwSetWindowShouldClose(window, true);
    }

    state->update(deltaTime);
    state->render();

    if (state->nextState() != NULL) {
      state = state->nextState();
      state->start();
    }

    input->endFrame();

    ImGui::Render();
    glfwSwapBuffers(window);
  }

  ImGui_ImplGlfwGL3_Shutdown();
  glfwTerminate();
}

void Application::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  Config* config = Config::instance();
  config->screenWidth = (float) width;
  config->screenHeight = (float) height;

  glViewport(0, 0, width, height);
}
