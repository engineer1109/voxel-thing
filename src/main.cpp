#include <string>
#include <iostream>

#include <E/application.hpp>

#ifdef _WINDOWS
#   pragma comment(lib, "openvr_api")
#endif

int main(int argc, char *argv[]) {
#ifdef _WINDOWS
  bool openEditor = false;

  for (int i = 0; i < argc; i++) {
    std::cout << argv[i] << std::endl;
    if (std::string(argv[i]) == "editor") openEditor = true;
  }

  E::Application app(!openEditor);
#else
  E::Application app(false);
#endif

  app.loop();

  return 0;
}
