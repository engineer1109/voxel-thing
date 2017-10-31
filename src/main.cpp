#include <E/application.hpp>

#ifdef _WINDOWS
#   pragma comment(lib, "openvr_api")
#endif

int main(void) {
  bool isVR = false;
  E::Application app(isVR);

  app.loop();

  return 0;
}
