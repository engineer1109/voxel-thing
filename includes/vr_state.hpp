#ifndef VR_STATE_H
#define VR_STATE_H

#include <state.hpp>

class VRState : public State {
  using State::State;

  void start();
  void render();
};

#endif
