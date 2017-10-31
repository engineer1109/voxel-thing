#include <render_manager.hpp>

RenderManager::RenderManager() {
  worldRenderer = new WorldRenderer();
  tooltipRenderer = new TooltipRenderer();
}

void RenderManager::preRender() {
  worldRenderer->preRender();
  tooltipRenderer->preRender();
}

void RenderManager::render(View view) {
  worldRenderer->render(view);
  tooltipRenderer->render(view);
}

void RenderManager::add(World *w) {
  worldRenderer->add(w);
}

void RenderManager::add(Tooltip *t) {
  tooltipRenderer->add(t);
}
