#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>

class State;

struct Entity {
  State *state;

  unsigned int flags = 0;

  void _init(State *s) { state = s; init(); }

  virtual void init() {};
  virtual void tick(float dt) {};
  virtual void debug() {};
};

struct Player : public Entity {
  float speed = 5.0f;

  glm::vec3 position;
  glm::vec3 facing;
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

  void init();
  void tick(float dt);
  void debug();
};

#endif
