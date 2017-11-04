#include <editor/editor_info_pane.hpp>

#include <imgui.h>

#include <E/state.hpp>

void editor::EditorInfoPane::tick(float dt) {
  ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 1.0f, 1.0f, 0.3f));
  ImGui::SetNextWindowPos(ImVec2(0, 0));

  ImGui::Begin("Editor Info", NULL, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_AlwaysAutoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoSavedSettings);

  ImGui::Text("A long night on Sontaya [0.1]");

  ImGui::Separator();

  ImGui::Text("Camera");
  ImGui::Indent(10.0f);
  ImGui::Text("position: (%.1f,%.1f,%.1f)", state->camera->position->x, state->camera->position->y, state->camera->position->y);
  ImGui::Text("facing: (%.1f,%.1f,%.1f)", state->camera->facing->x, state->camera->facing->y, state->camera->facing->y);

  ImGui::Unindent();

  ImGui::Separator();

  if (ImGui::Button("Save")) {
    state->world->save(state->config->worldFilePath);
  }

  ImGui::End();
  ImGui::PopStyleColor();
}


