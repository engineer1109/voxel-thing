#include <camera.hpp>

#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <utils.hpp>
#include <state.hpp>

glm::mat4 Camera::projectionMatrix() {
  return glm::perspective(glm::radians(95.0f), SCREEN_WIDTH/SCREEN_HEIGHT, 0.1f, 100.0f);
}

glm::mat4 Camera::viewMatrix() {
  return glm::lookAt(*position, *position + *facing, UP);
}

glm::vec3 Camera::screenToDirection(glm::vec2 p) {
  // convert screen coordinates to normalized device coordinates (clip space).
  float x = (2.0f*p.x) / SCREEN_WIDTH - 1;
  float y = (2.0f*p.y) / SCREEN_HEIGHT - 1;

  std::cout << "x: " << x << std::endl;
  std::cout << "y: " << y << std::endl;

  glm::vec4 clipCoords(x, y, -1.0f, 1.0f);

  // convert from clip space to eye space
  glm::mat4 invertedProj = glm::inverse(projectionMatrix());
  glm::vec4 eyeCoords = invertedProj * clipCoords;
  eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);

  std::cout << "ex: " << eyeCoords.x << std::endl;
  std::cout << "ey: " << eyeCoords.y << std::endl;

  // convert from eye space to world space
  glm::mat4 invertedView = glm::inverse(viewMatrix());
  glm::vec4 rayWorld = invertedView * eyeCoords;

  std::cout << "wx: " << rayWorld.x << std::endl;
  std::cout << "wy: " << rayWorld.y << std::endl;

  return glm::normalize(glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z));
}
