#include <game_state.hpp>

#include <iostream>

void GameState::start() {
  world = new World(config->worldFilePath);

  renderer->add(world);

  player = new Player;
  add(player);

  StateSwitcher *stateSwitcher = new StateSwitcher();
  add(stateSwitcher);
}
