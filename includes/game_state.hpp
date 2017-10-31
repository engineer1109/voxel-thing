#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <state.hpp>
#include <entity.hpp>

class GameState : public State {
  public:
    using State::State;

    void start();
};

#endif
