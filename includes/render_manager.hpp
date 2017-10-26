#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include <world.hpp>
#include <world_renderer.hpp>
#include <tooltip_renderer.hpp>
#include <camera.hpp>
#include <config.hpp>
#include <entity.hpp>

class RenderManager {
  public:
    RenderManager();

    void render(Camera *camera, Config *config);

    void add(World *w);
    void add(Tooltip *t);
  private:
    WorldRenderer *worldRenderer;
    TooltipRenderer *tooltipRenderer;
};

#endif
