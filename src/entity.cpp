#include <entity.hpp>

#include <iostream>

#include <game.hpp>

Player::Player() {
  position = glm::vec3(0.0f, 2.0f, 0.0f);
  facing = glm::vec3(0.0f, 0.0f, -1.0f);
}

void Player::tick(float dt) {
  if (game->input->keys->down(GLFW_KEY_W)) {
    position += speed * dt * facing;
  }

  if (game->input->keys->down(GLFW_KEY_S)) {
    position -= speed * dt * facing;
  }

  if (game->input->keys->down(GLFW_KEY_A)) {
    position -= glm::normalize(glm::cross(facing, up)) * speed * dt;
  }

  if (game->input->keys->down(GLFW_KEY_D)) {
    position += glm::normalize(glm::cross(facing, up)) * speed * dt;
  }
}

void Player::debug() {
  std::cout << "position:" << std::endl;

  std::cout << "x" << position.x << std::endl;
  std::cout << "y" << position.y << std::endl;
  std::cout << "z" << position.z << std::endl;

  // ImGui::Text("position: (%.1f,%.1f,%.1f)", position.x, position.y, position.z);
}
