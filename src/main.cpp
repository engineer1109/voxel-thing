#include <string>
#include <iostream>

#include <E/application.hpp>

#include <editor/editor.hpp>
#include <game.hpp>

int main(int argc, char *argv[]) {
  E::Application *app;
#ifdef _WINDOWS
  bool editor = false;

  for (int i = 0; i < argc; i++) {
    if (std::string(argv[i]) == "editor") editor = true;
  }

  if (editor) {
    app = new editor::Editor();
  } else {
    app = new Game();
  }

#else
  app = new editor::Editor();
#endif

  app->loop();

  return 0;
}
