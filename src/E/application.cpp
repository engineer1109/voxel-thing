#include <E/application.hpp>

#include <stdexcept>
#include <iostream>

#include <glad/glad.h>
#include <stb_image.h>

#include <E/config.hpp>
#include <E/input.hpp>

E::Application::Application() {
  Config* config = Config::instance();
  Input* input = Input::instance();

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  window = glfwCreateWindow(config->screenWidth, config->screenHeight, "openvr test", NULL, NULL);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(0);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialise GLAD");
  }

  glEnable(GL_DEPTH_TEST);

  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glfwSetKeyCallback(window, Input::keyCallback);
  glfwSetMouseButtonCallback(window, Input::mouseButtonCallback);
  glfwSetCursorPosCallback(window, Input::mouseMovementCallback);
  glfwSetCursorPosCallback(window, Input::mouseMovementCallback);
  glfwSetScrollCallback(window, Input::mouseScrollCallback);
}

void E::Application::use(Context *ctx) {
  context = ctx;

  context->init();
}

void E::Application::loop() {
  state->start();

  while (!glfwWindowShouldClose(window)) {
    float deltaTime = (float) glfwGetTime() - lastTime;
    lastTime = (float) glfwGetTime();

    glfwPollEvents();

    Input *input = Input::instance();

    input->update();

    if (input->keys->justDown(GLFW_KEY_ESCAPE)) {
      glfwSetWindowShouldClose(window, true);
    }

    context->preFrame();

    state->update(deltaTime);

    context->render(state->renderer);
    context->postFrame();

    if (state->nextState() != NULL) {
      state = state->nextState();
      state->start();
    }

    input->endFrame();

    glfwSwapBuffers(window);
  }

  //ImGui_ImplGlfwGL3_Shutdown();
  glfwTerminate();
}

void E::Application::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  Config* config = Config::instance();
  config->screenWidth = (float) width;
  config->screenHeight = (float) height;

  glViewport(0, 0, width, height);
}
