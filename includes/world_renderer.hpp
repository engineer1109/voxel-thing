#ifndef WORLD_RENDERER_H
#define WORLD_RENDERER_H

#include <E/renderer.hpp>
#include <E/camera.hpp>
#include <E/config.hpp>
#include <E/shader.hpp>
#include <E/texture.hpp>
#include <E/view.hpp>

#include <world.hpp>

class WorldRenderer : public E::Renderer {
  public:
    WorldRenderer();

    bool shouldRender();
    void preRender();
    void render(E::View view);

    void add(World *w);
  private:
    World *world = NULL;

    E::Shader *shader;
    E::Texture *texture;
};

#endif
