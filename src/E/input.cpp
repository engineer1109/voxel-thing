#include <E/input.hpp>

E::Input::Input() {
  keys = new KeyManager();
}

void E::Input::update() {
  keys->update();
}

void E::Input::endFrame() {
  mouseMoved = false;

  deltaMouseScrollX = 0;
  deltaMouseScrollY = 0;
}

double E::Input::deltaMouseX() {
  if (!mouseMoved) {
    return 0;
  }

  if (!lastMouseX || !mouseX) {
    return 0;
  }

  return lastMouseX - mouseX;
}

double E::Input::deltaMouseY() {
  if (!mouseMoved) {
    return 0;
  }

  if (!lastMouseY || !mouseY) {
    return 0;
  }

  return lastMouseY - mouseY;
}

bool E::Input::mouseClicked() {
  return (!lastMousePrimaryPressed && mousePrimaryPressed);
}

E::Input* E::Input::instance() {
  if (!s_instance) {
    s_instance = new Input();
  }

  return s_instance;
}

void E::Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  Input* input = Input::instance();

  if (action != GLFW_PRESS && action != GLFW_RELEASE) {
    return;
  }

  input->keys->set(key, action == GLFW_PRESS);
}

void E::Input::mouseButtonCallback(GLFWwindow *window, int button, int action, int mode) {
  Input* input = Input::instance();

  input->lastMousePrimaryPressed = input->mousePrimaryPressed;

  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    input->mousePrimaryPressed = true;
  } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
    input->mousePrimaryPressed = false;
  }
}

void E::Input::mouseMovementCallback(GLFWwindow *window, double x, double y) {
  Input* input = Input::instance();

  input->mouseMoved = true;

  input->lastMouseX = input->mouseX;
  input->lastMouseY = input->mouseY;

  input->mouseX = x;
  input->mouseY = y;
}

void E::Input::mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
  Input *input = Input::instance();

  input->deltaMouseScrollX = xOffset;
  input->deltaMouseScrollY = yOffset;
}

E::Input* E::Input::s_instance;
