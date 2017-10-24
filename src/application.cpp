#include <application.hpp>

#include <stdexcept>
#include <iostream>

#include <glad/glad.h>
#include <stb_image.h>

#include <key_manager.hpp>

KeyManager KEYS;

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
  glfwSetKeyCallback(window, keyCallback);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialise GLAD");
  }

  glEnable(GL_DEPTH_TEST);

  glViewport(0, 0, SCREEN_WIDTH, SCREEN_WIDTH);

  stbi_set_flip_vertically_on_load(true);

  game = new Game(window);
}

void Application::loop() {
  while (!glfwWindowShouldClose(window)) {
    float deltaTime = (float) glfwGetTime() - lastTime;
    lastTime = (float) glfwGetTime();

    glfwPollEvents();

    KEYS.update();

    if (KEYS.justDown(GLFW_KEY_ESCAPE)) {
      glfwSetWindowShouldClose(window, true);
    }

    game->update(deltaTime);
    game->render();

    glfwSwapBuffers(window);
  }
}

void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (action != GLFW_PRESS && action != GLFW_RELEASE) {
    return;
  }

  KEYS.set(key, action == GLFW_PRESS);
}

void Application::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
