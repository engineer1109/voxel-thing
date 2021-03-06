#include <E/camera.hpp>

#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <E/utils.hpp>
#include <E/config.hpp>
#include <E/state.hpp>

E::Camera::Camera() {
  cameras.push_back(this);
}

E::Camera::~Camera() {
  for (int i = 0; i < cameras.size(); i++) {
    if (cameras[i] == this) {
      cameras.erase(cameras.begin() + i);

      break;
    }
  }
}

glm::mat4 E::Camera::projectionMatrix() {
  Config *config = Config::instance();

  return glm::perspective(glm::radians(70.0f), config->screenWidth/config->screenHeight, 0.1f, 100.0f);
}

glm::mat4 E::Camera::viewMatrix() {
  return glm::lookAt(*position, *position + *facing, UP);
}

glm::vec3 E::Camera::screenToDirection(glm::vec2 p) {
  Config *config = Config::instance();

  // convert screen coordinates to normalized device coordinates (clip space).
  float x = (2.0f*p.x) / config->screenWidth - 1;
  float y = (2.0f*p.y) / config->screenHeight - 1;

  glm::vec4 clipCoords(x, -y, -1.0f, 1.0f);

  // convert from clip space to eye space
  glm::mat4 invertedProj = glm::inverse(projectionMatrix());
  glm::vec4 eyeCoords = invertedProj * clipCoords;
  eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);

  // convert from eye space to world space
  glm::mat4 invertedView = glm::inverse(viewMatrix());
  glm::vec4 rayWorld = invertedView * eyeCoords;

  return glm::normalize(glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z));
}

E::Camera* E::Camera::main() {
  Camera* cam;
  if (cameras.size() == 0) {
    cam = new Camera();
  } else {
    cam = cameras.front();
  }

  return cam;
}

std::vector<E::Camera*> E::Camera::cameras;
