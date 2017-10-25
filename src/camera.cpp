#include <camera.hpp>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include <utils.hpp>

glm::mat4 Camera::viewMatrix() {
  return glm::lookAt(*position, *position + *facing, UP);
}
