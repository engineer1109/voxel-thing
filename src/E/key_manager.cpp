#include <E/key_manager.hpp>

E::KeyManager::KeyManager() {}

bool E::KeyManager::down(int key) {
  return get(key) == KeyStateDown;
}

bool E::KeyManager::justDown(int key) {
  return get(key) == KeyStateJustDown;
}

bool E::KeyManager::up(int key) {
  return get(key) == KeyStateUp;
}

E::KeyState E::KeyManager::get(int key) {
  return state[key];
}

void E::KeyManager::set(int key, bool pressed) {
  rawState[key] = pressed;
}

void E::KeyManager::update() {
  for (auto& pair : rawState) {
    if (pair.second) {
      if (state[pair.first] == KeyStateUp || state[pair.first] == KeyStateJustUp) {
        state[pair.first] = KeyStateJustDown;
      } else {
        state[pair.first] = KeyStateDown;
      }
    } else {
      if (state[pair.first] == KeyStateDown || state[pair.first] == KeyStateJustDown) {
        state[pair.first] = KeyStateJustUp;
      } else {
        state[pair.first] = KeyStateUp;
      }
    }
  }
}
