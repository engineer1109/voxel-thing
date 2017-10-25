#include <application.hpp>

#include <stdexcept>
#include <iostream>

#include <glad/glad.h>
#include <stb_image.h>

#include <input.hpp>
#include <game_state.hpp>

Application::Application() {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "game", NULL, NULL);

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

  glViewport(0, 0, SCREEN_WIDTH, SCREEN_WIDTH);

  stbi_set_flip_vertically_on_load(true);

  Input* input = Input::instance();

  glfwSetKeyCallback(window, Input::keyCallback);
  glfwSetMouseButtonCallback(window, Input::mouseButtonCallback);
  glfwSetCursorPosCallback(window, Input::mouseMovementCallback);

  state = new GameState(input);
  state->start();
}

void Application::loop() {
  while (!glfwWindowShouldClose(window)) {
    float deltaTime = (float) glfwGetTime() - lastTime;
    lastTime = (float) glfwGetTime();

    glfwPollEvents();

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

    glfwSwapBuffers(window);
  }
}

void Application::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
