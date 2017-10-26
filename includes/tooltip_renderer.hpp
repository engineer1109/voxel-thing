#ifndef TOOLTIP_RENDERER_H
#define TOOLTIP_RENDERER_H

#include <renderer.hpp>
#include <camera.hpp>
#include <config.hpp>
#include <entity.hpp>
#include <shader.hpp>
#include <mesh.hpp>

class TooltipRenderer : public Renderer {
  public:
    TooltipRenderer();

    void render(Camera *camera, Config *config);

    void add(Tooltip *t);
  private:
    std::vector<Tooltip*> tooltips;

    Shader *shader;
    Mesh *mesh;
};

#endif
