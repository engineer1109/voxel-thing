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
  float speed = 10.0f;

  glm::vec3 position;
  glm::vec3 facing;

  void init();
  void tick(float dt);
  void debug();

  private:
    float sensitivity = 0.3;
    float pitch = 0;
    float yaw = 0;
};

struct Cursor : public Entity {
  float speed = 10.0f;

  glm::vec3 position;
  glm::vec3 facing;

  void init();
  void tick(float dt);

  private:
    float sensitivity = 0.3;
    float pitch = 0;
    float yaw = 0;
};

struct Tooltip : public Entity {
  glm::vec3 position;

  glm::vec3 color = { 1.0f, 0.0f, 0.0f };

  void init();
  void tick(float dt);
};

#endif
