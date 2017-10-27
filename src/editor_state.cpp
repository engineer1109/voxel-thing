#include <editor_state.hpp>

#include <iostream>

#include <imgui.h>

#include <entity.hpp>

void EditorState::start() {
  world = new World(config->worldFilePath);

  renderer->add(world);

  Cursor *cursor = new Cursor();
  add(cursor);

  Tooltip *tooltip = new Tooltip();
  add(tooltip);

  EditorInfoPane *pane = new EditorInfoPane();
  add(pane);

  ImGuiIO& io = ImGui::GetIO();
  io.MouseDrawCursor = true;
}
