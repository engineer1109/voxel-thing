#include <input.hpp>

Input::Input() {
  keys = new KeyManager();
}

void Input::update() {
  keys->update();
}

Input* Input::instance() {
  if (!s_instance) {
    s_instance = new Input();
  }

  return s_instance;
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  Input* input = Input::instance();

  if (action != GLFW_PRESS && action != GLFW_RELEASE) {
    return;
  }

  input->keys->set(key, action == GLFW_PRESS);
}

void Input::mouseButtonCallback(GLFWwindow *window, int button, int action, int mode) {
  Input* input = Input::instance();

  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    input->mousePrimaryPressed = true;
  } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
    input->mousePrimaryPressed = false;
  }
}

void Input::mouseMovementCallback(GLFWwindow *window, double x, double y) {
  Input* input = Input::instance();

  input->mouseX = x;
  input->mouseY = y;
}

Input* Input::s_instance;
