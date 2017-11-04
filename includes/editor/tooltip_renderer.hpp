#ifndef TOOLTIP_RENDERER_H
#define TOOLTIP_RENDERER_H

#include <E/renderer.hpp>
#include <E/camera.hpp>
#include <E/config.hpp>
#include <E/shader.hpp>
#include <E/mesh.hpp>
#include <E/view.hpp>

#include <block.hpp>
#include <editor/tooltip.hpp>

namespace editor {
  class TooltipRenderer : public E::Renderer {
    public:
      TooltipRenderer();

      bool shouldRender();

      void render(E::View view);

      void add(Tooltip *t);
    private:
      std::vector<Tooltip*> tooltips;

      E::Shader *shader;
      E::Mesh *mesh;

      void rotationForSide(BlockSide side, glm::vec3 *axis, float *degrees);
  };
};

#endif
