#include <editor/tooltip.hpp>

#include <imgui.h>

#include <E/state.hpp>

void editor::Tooltip::init() {
  state->renderer->add(this);
}

void editor::Tooltip::tick(float dt) {
  getBlockToPlace();

  glm::vec3 p = state->camera->screenToDirection(glm::vec2(state->input->mouseX, state->input->mouseY));
  E::RayHit ray = state->world->ray(*state->camera->position, p);

  if (!ray.didHit) {
    shouldRender = false;

    return;
  }

  side = diff(ray.chunk, ray.block, ray.prevChunk, ray.prevBlock);

  shouldRender = true;

  position.x = ray.chunk.x * CHUNK_WIDTH + ray.block.x + 0.5f;
  position.y = ray.block.y + 0.5f;
  position.z = ray.chunk.z * CHUNK_DEPTH + ray.block.z + 0.5f;

  if (state->input->mouseClicked()) {
    if (state->input->keys->down(GLFW_KEY_X)) {
      state->world->chunks[ray.chunk.z][ray.chunk.x]->data[ray.block.y][ray.block.z][ray.block.x] = EMPTY;
    } else {
      state->world->chunks[ray.prevChunk.z][ray.prevChunk.x]->data[ray.prevBlock.y][ray.prevBlock.z][ray.prevBlock.x] = blockTypeToPlace;
    }

    state->input->mousePrimaryPressed = false;
    state->world->reloadChunks();
  }
}

void editor::Tooltip::getBlockToPlace() {
  ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x/2, 0), ImGuiCond_Always, ImVec2(0.5, 0.5));
  ImGui::Begin("Block choice!", NULL, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_AlwaysAutoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoSavedSettings);

  for (auto& pair : state->world->blocks->blocks) {
    ImGui::RadioButton(pair.second.name.c_str(), &blockTypeToPlace, pair.second.id);
    ImGui::SameLine();
  }

  ImGui::End();
}

BlockSide editor::Tooltip::diff(E::Index chunk1, E::Index block1, E::Index chunk2, E::Index block2) {
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
