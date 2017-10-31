#include <application.hpp>

#ifdef _WINDOWS
#   pragma comment(lib, "openvr_api")
#endif

int main(void) {
  bool isVR = true;
  Application app(isVR);

  app.loop();

  return 0;
}
