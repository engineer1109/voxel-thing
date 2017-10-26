#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <state.hpp>
#include <entity.hpp>
#include <world.hpp>
#include <shader.hpp>
#include <texture.hpp>

class GameState : public State {
  public:
    using State::State;

    void start();
    void render();
  private:
    Player *player;

    World *world;

    Shader *worldShader;
    Texture *worldTexture;
};

#endif
