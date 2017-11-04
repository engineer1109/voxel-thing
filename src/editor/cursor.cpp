#include <editor/cursor.hpp>

#include <GLFW/glfw3.h>

#include <E/state.hpp>

void editor::Cursor::init() {
  state->camera->position = &position;
  state->camera->facing = &facing;
}

void editor::Cursor::tick(float dt) {
  // change orientation

  if (state->input->keys->down(GLFW_KEY_LEFT_ALT)) {
    double xOffset = state->input->deltaMouseX();
    double yOffset = state->input->deltaMouseY();

    yaw -= xOffset * sensitivity * 2;
    pitch += yOffset * sensitivity * 2;

    pitch = E::clamp(pitch, -89.0f, 89.0f);

    glm::vec3 tfront = {
      cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
      sin(glm::radians(pitch)),
      sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    };

    facing = glm::normalize(tfront);
  }

  // translate up/down/left/right
  if (state->input->keys->down(GLFW_KEY_LEFT_SHIFT)) {
    glm::vec3 t = {
      (float)state->input->deltaMouseX() * sensitivity,
      (float)state->input->deltaMouseY() * sensitivity,
      0
    };

    if (abs(t.x) > abs(t.y)) {
      position -= glm::normalize(glm::cross(facing, E::UP)) * t.x;
    } else {
      position.y += t.y;
    }
  }

  // translate forward/back
  if (state->input->deltaMouseScrollY != 0) {
    position += ((float)state->input->deltaMouseScrollY) * 50.0f * dt * facing;
  }
}
