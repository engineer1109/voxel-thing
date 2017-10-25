#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>

class Game;

struct Entity {
  Game *game;

  unsigned int flags = 0;

  void init(Game *g) { game = g; }

  virtual void tick(float dt) {};

  virtual void debug() {};
};

struct Player : public Entity {
  Player();

  float speed = 5.0f;

  glm::vec3 position;
  glm::vec3 facing;
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

  void tick(float dt);

  void debug();
};

#endif
