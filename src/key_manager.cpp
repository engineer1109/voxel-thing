#include <key_manager.hpp>

KeyManager::KeyManager() {}

bool KeyManager::down(int key) {
  return get(key) == KeyStateDown;
}

bool KeyManager::justDown(int key) {
  return get(key) == KeyStateJustDown;
}

bool KeyManager::up(int key) {
  return get(key) == KeyStateUp;
}

KeyState KeyManager::get(int key) {
  return state[key];
}

void KeyManager::set(int key, bool pressed) {
  rawState[key] = pressed;
}

void KeyManager::update() {
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
