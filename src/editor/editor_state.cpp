#include <editor/editor_state.hpp>

#include <iostream>

#include <imgui.h>

#include <editor/cursor.hpp>
#include <editor/editor_info_pane.hpp>
#include <editor/state_switcher.hpp>

void editor::EditorState::start() {
  world = new World(config->worldFilePath);

  renderer->add(world);

  Cursor *cursor = new Cursor();
  add(cursor);

  Tooltip *tooltip = new Tooltip();
  add(tooltip);

  EditorInfoPane *pane = new EditorInfoPane();
  add(pane);

  StateSwitcher *stateSwitcher = new StateSwitcher();
  add(stateSwitcher);

  ImGuiIO& io = ImGui::GetIO();
  io.MouseDrawCursor = true;
}
