#include <entity.hpp>

#include <iostream>

#include <editor_state.hpp>
#include <state.hpp>

void Player::init() {
  position = glm::vec3(0.0f, 2.0f, 0.0f);
  facing = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Player::tick(float dt) {
  if (state->input->keys->down(GLFW_KEY_W)) {
    position += speed * dt * facing;
  }

  if (state->input->keys->down(GLFW_KEY_S)) {
    position -= speed * dt * facing;
  }

  if (state->input->keys->down(GLFW_KEY_A)) {
    position -= glm::normalize(glm::cross(facing, up)) * speed * dt;
  }

  if (state->input->keys->down(GLFW_KEY_D)) {
    position += glm::normalize(glm::cross(facing, up)) * speed * dt;
  }

  if (state->input->keys->justDown(GLFW_KEY_F5)) {
    state->changeState(new EditorState(state->input));
  }
}

void Player::debug() {
  // ImGui::Text("position: (%.1f,%.1f,%.1f)", position.x, position.y, position.z);
}
