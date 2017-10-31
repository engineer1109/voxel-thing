#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include <view.hpp>
#include <world.hpp>
#include <world_renderer.hpp>
#include <tooltip_renderer.hpp>
#include <camera.hpp>
#include <config.hpp>
#include <entity.hpp>

class RenderManager {
  public:
    RenderManager();

    void preRender();
    void render(View view);

    void add(World *w);
    void add(Tooltip *t);
  private:
    WorldRenderer *worldRenderer;
    TooltipRenderer *tooltipRenderer;
};

#endif