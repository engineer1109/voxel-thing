#pragma once

#include <E/application.hpp>
#include <E/screen_context.hpp>
#include <E/config.hpp>
#include <E/input.hpp>

#include <editor/editor_state.hpp>

namespace editor {
  class Editor : public E::Application {
    public:
      Editor() : Application() {
        E::Config *config = E::Config::instance();

        auto ctx = new E::ScreenContext(window, config);
        use(ctx);

        state = new editor::EditorState(config, E::Input::instance());
      }
  };
};
