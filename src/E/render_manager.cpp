#include <E/render_manager.hpp>

E::RenderManager::RenderManager() {
  worldRenderer = new WorldRenderer();
  tooltipRenderer = new editor::TooltipRenderer();
}

void E::RenderManager::preRender() {
  worldRenderer->preRender();
  tooltipRenderer->preRender();
}

void E::RenderManager::render(View view) {
  worldRenderer->render(view);
  tooltipRenderer->render(view);
}

void E::RenderManager::add(World *w) {
  worldRenderer->add(w);
}

void E::RenderManager::add(editor::Tooltip *t) {
  tooltipRenderer->add(t);
}
