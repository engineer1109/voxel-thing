#include <camera.hpp>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include <utils.hpp>
#include <game.hpp>

void Camera::update(float deltaTime) {
  if (KEYS.down(GLFW_KEY_W)) {
    pos += speed * deltaTime * front;
  }

  if (KEYS.down(GLFW_KEY_S)) {
    pos -= speed * deltaTime * front;
  }

  if (KEYS.down(GLFW_KEY_A)) {
    pos -= glm::normalize(glm::cross(front, up)) * speed * deltaTime;
  }

  if (KEYS.down(GLFW_KEY_D)) {
    pos += glm::normalize(glm::cross(front, up)) * speed * deltaTime;
  }
}

void Camera::mouseCallback(double x, double y) {
  if (firstMouse) {
    lastMouseX = x;
    lastMouseY = y;

    firstMouse = false;
  }

  double xOffset = lastMouseX - x;
  double yOffset = lastMouseY - y;

  yaw -= xOffset * sensitivity;
  pitch += yOffset * sensitivity;

  pitch = clamp(pitch, -89.0f, 89.0f);

  glm::vec3 tfront = {
    cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
    sin(glm::radians(pitch)),
    sin(glm::radians(yaw)) * cos(glm::radians(pitch))
  };

  front = glm::normalize(tfront);

  lastMouseX = x;
  lastMouseY = y;
}

glm::mat4 Camera::projectionMatrix() {
  return glm::lookAt(pos, pos + front, up);
}
