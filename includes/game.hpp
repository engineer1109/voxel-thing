#ifndef GAME_H
#define GAME_H

#include <vector>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <input.hpp>
#include <camera.hpp>
#include <world.hpp>
#include <entity.hpp>
#include <shader.hpp>
#include <texture.hpp>

const float SCREEN_WIDTH=1600.0f;
const float SCREEN_HEIGHT=900.0f;

class Game {
  public:
    Game(Input *i);

    Camera camera;

    Input *input;

    std::vector<Entity*> entities;

    void update(float dt);
    void render();
  private:
    void add(Entity* e);

    Player *player;

    World *world;

    Shader *worldShader;
    Texture *worldTexture;
};

#endif
