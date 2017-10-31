#ifndef WORLD_RENDERER_H
#define WORLD_RENDERER_H

#include <renderer.hpp>
#include <world.hpp>
#include <camera.hpp>
#include <config.hpp>
#include <shader.hpp>
#include <texture.hpp>
#include <view.hpp>

class WorldRenderer : public Renderer {
  public:
    WorldRenderer();

    void preRender();
    void render(View view);

    void add(World *w);
  private:
    World *world = NULL;

    Shader *shader;
    Texture *texture;
};

#endif
