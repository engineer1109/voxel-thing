#include <render_manager.hpp>

RenderManager::RenderManager() {
  worldRenderer = new WorldRenderer();
  tooltipRenderer = new TooltipRenderer();
}

void RenderManager::render(Camera *camera, Config *config) {
  glClearColor(0, 0, 0, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  worldRenderer->render(camera, config);
  tooltipRenderer->render(camera, config);
}

void RenderManager::add(World *w) {
  worldRenderer->add(w);
}

void RenderManager::add(Tooltip *t) {
  tooltipRenderer->add(t);
}
