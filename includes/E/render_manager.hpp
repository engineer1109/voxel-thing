#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include <E/view.hpp>
#include <E/camera.hpp>
#include <E/config.hpp>
#include <E/entity.hpp>

#include <world.hpp>
#include <world_renderer.hpp>
#include <editor/tooltip.hpp>
#include <editor/tooltip_renderer.hpp>

namespace E {
  class RenderManager {
    public:
      RenderManager();

      void preRender();
      void render(View view);

      void add(World *w);
      void add(editor::Tooltip *t);
    private:
      WorldRenderer *worldRenderer;
      editor::TooltipRenderer *tooltipRenderer;
  };
}

#endif
