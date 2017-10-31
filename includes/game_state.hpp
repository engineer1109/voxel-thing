#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <E/state.hpp>
#include <entity.hpp>

class GameState : public E::State {
  public:
    using State::State;

    void start();
};

#endif
