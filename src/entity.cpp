#include <entity.hpp>

#include <iostream>

#include <utils.hpp>
#include <editor_state.hpp>
#include <state.hpp>

void Player::init() {
  state->camera.position = &position;
  state->camera.facing = &facing;
}

void Player::tick(float dt) {
  if (state->input->keys->down(GLFW_KEY_W)) {
    position += speed * dt * facing;
  }

  if (state->input->keys->down(GLFW_KEY_S)) {
    position -= speed * dt * facing;
  }

  if (state->input->keys->down(GLFW_KEY_A)) {
    position -= glm::normalize(glm::cross(facing, UP)) * speed * dt;
  }

  if (state->input->keys->down(GLFW_KEY_D)) {
    position += glm::normalize(glm::cross(facing, UP)) * speed * dt;
  }

  if (state->input->keys->justDown(GLFW_KEY_F5)) {
    state->changeState(new EditorState(state->input));
  }

  double xOffset = state->input->deltaMouseX();
  double yOffset = state->input->deltaMouseY();

  yaw -= xOffset * sensitivity;
  pitch += yOffset * sensitivity;

  pitch = clamp(pitch, -89.0f, 89.0f);

  glm::vec3 tfront = {
    cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
    sin(glm::radians(pitch)),
    sin(glm::radians(yaw)) * cos(glm::radians(pitch))
  };

  facing = glm::normalize(tfront);
}

void Player::debug() {
  // ImGui::Text("position: (%.1f,%.1f,%.1f)", position.x, position.y, position.z);
}
