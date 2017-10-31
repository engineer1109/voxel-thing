#include <state_switcher.hpp>

#include <GLFW\glfw3.h>

#include <E/state.hpp>

#include <editor_state.hpp>
#include <game_state.hpp>

void StateSwitcher::tick(float dt) {
  if (state->input->keys->justDown(GLFW_KEY_F5)) {
    state->changeState(new EditorState(state->config, state->input));
  }

  if (state->input->keys->justDown(GLFW_KEY_F6)) {
    state->changeState(new GameState(state->config, state->input));
  }
}
