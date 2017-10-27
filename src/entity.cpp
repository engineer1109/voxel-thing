#include <entity.hpp>

#include <math.h>
#include <iostream>

#include <imgui.h>

#include <chunk.hpp>
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
    state->changeState(new EditorState(state->config, state->input));
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

void Cursor::init() {
  state->camera.position = &position;
  state->camera.facing = &facing;
}

void Cursor::tick(float dt) {
  // change orientation
  if (state->input->keys->down(GLFW_KEY_LEFT_ALT)) {
    double xOffset = state->input->deltaMouseX();
    double yOffset = state->input->deltaMouseY();

    yaw -= xOffset * sensitivity * 2;
    pitch += yOffset * sensitivity * 2;

    pitch = clamp(pitch, -89.0f, 89.0f);

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
      position -= glm::normalize(glm::cross(facing, UP)) * t.x;
    } else {
      position.y += t.y;
    }
  }

  // translate forward/back
  if (state->input->deltaMouseScrollY != 0) {
    position += ((float)state->input->deltaMouseScrollY) * 50.0f * dt * facing;
  }
}

void Tooltip::init() {
  state->renderer->add(this);
}

void Tooltip::tick(float dt) {
  glm::vec3 p = state->camera.screenToDirection(glm::vec2(state->input->mouseX, state->input->mouseY));
  RayHit ray = state->world->ray(*state->camera.position, p);

  if (!ray.didHit) {
    shouldRender = false;

    return;
  }

  shouldRender = true;

  position.x = ray.chunk.x * CHUNK_WIDTH + ray.block.x + 0.5f;
  position.y = ray.block.y + 0.5f;
  position.z = ray.chunk.z * CHUNK_DEPTH + ray.block.z + 0.5f;

  // place block
  if (state->input->mouseClicked()) {
    state->world->chunks[ray.prevChunk.z][ray.prevChunk.x]->data[ray.prevBlock.y][ray.prevBlock.z][ray.prevBlock.x] = SOLID;
    state->world->reloadChunks();

    state->input->mousePrimaryPressed = false;
  }

  side = diff(ray.chunk, ray.block, ray.prevChunk, ray.prevBlock);
}

BlockSide Tooltip::diff(Index chunk1, Index block1, Index chunk2, Index block2) {
  glm::vec3 a = {};
  a.x = chunk1.x * CHUNK_WIDTH + block1.x;
  a.y = block1.y;
  a.z = chunk1.z * CHUNK_WIDTH + block1.z;

  glm::vec3 b = {};
  b.x = chunk2.x * CHUNK_WIDTH + block2.x;
  b.y = block2.y;
  b.z = chunk2.z * CHUNK_WIDTH + block2.z;

  glm::vec3 c = a - b;

  if (c.y == -1) {
    return TOP;
  } else if (c.y == 1) {
    return BOTTOM;
  } else if (c.x == -1) {
    return LEFT;
  } else if (c.x == 1) {
    return RIGHT;
  } else if (c.z == -1) {
    return BACK;
  } else if (c.z == 1) {
    return FRONT;
  }

  return FRONT;
}

void EditorInfoPane::tick(float dt) {
  ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 1.0f, 1.0f, 0.3f));
  ImGui::SetNextWindowPos(ImVec2(0, 0));

  ImGui::Begin("Editor Info", NULL, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_AlwaysAutoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoSavedSettings);

  ImGui::Text("A long night on Sontaya [0.1]");

  ImGui::Separator();

  ImGui::Text("Camera");
  ImGui::Indent(10.0f);
  ImGui::Text("position: (%.1f,%.1f,%.1f)", state->camera.position->x, state->camera.position->y, state->camera.position->y);
  ImGui::Text("facing: (%.1f,%.1f,%.1f)", state->camera.facing->x, state->camera.facing->y, state->camera.facing->y);

  ImGui::Unindent();

  ImGui::Separator();

  if (ImGui::Button("Save")) {
    state->world->save(state->config->worldFilePath);
  }

  ImGui::End();
  ImGui::PopStyleColor();
}
