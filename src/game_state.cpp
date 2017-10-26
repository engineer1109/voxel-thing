#include <game_state.hpp>

#include <iostream>

void GameState::start() {
  world = new World("world.json");

  renderer->add(world);

  player = new Player;
  add(player);
}
