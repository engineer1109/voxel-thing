#pragma once

#include <E/application.hpp>
#include <E/vr_context.hpp>
#include <E/config.hpp>
#include <E/input.hpp>

#include <game_state.hpp>

class Game : public E::Application {
  public:
    Game() : Application() {
      auto ctx = new E::VRContext();
      use(ctx);

      state = new GameState(E::Config::instance(), E::Input::instance());
    }
};
