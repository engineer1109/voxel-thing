#ifndef KEY_MANAGER_H
#define KEY_MANAGER_H

#include <map>

namespace E {
  enum KeyState {
    KeyStateUp,
    KeyStateJustUp,
    KeyStateDown,
    KeyStateJustDown
  };

  class KeyManager {
    public:
      KeyManager();

      bool down(int key);
      bool justDown(int key);
      bool up(int key);
      bool justUp(int key);

      KeyState get(int key);

      void set(int key, bool pressed);

      void update();
    private:
      std::map<int, KeyState> state;
      std::map<int, bool> rawState;
  };
}

#endif
