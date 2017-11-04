#include <E/render_manager.hpp>

#include <iostream>

E::RenderManager::RenderManager() {
  worldRenderer = new WorldRenderer();
  tooltipRenderer = new editor::TooltipRenderer();
}

void E::RenderManager::preRender() {
  if (tooltipRenderer->shouldRender()) tooltipRenderer->preRender();
  if (worldRenderer->shouldRender()) worldRenderer->preRender();
}

void E::RenderManager::render(View view) {
  if (worldRenderer->shouldRender()) worldRenderer->render(view);
  if (tooltipRenderer->shouldRender()) tooltipRenderer->render(view);
}

void E::RenderManager::add(World *w) {
  worldRenderer->add(w);
}

void E::RenderManager::add(editor::Tooltip *t) {
  tooltipRenderer->add(t);
}
