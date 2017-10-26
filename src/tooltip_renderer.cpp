#include <tooltip_renderer.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

TooltipRenderer::TooltipRenderer() {
  std::vector<float> quad = {
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f,
  };

  shader = new Shader("shaders/tooltip.vert", "shaders/tooltip.frag");
  mesh = new Mesh(quad, { VEC3_VERTEX_ATTRIB });
  mesh->bind();
}

void TooltipRenderer::render(Camera *camera, Config *config) {
  shader->use();

  glm::mat4 view = camera->viewMatrix();
  glm::mat4 projection = camera->projectionMatrix();

  shader->setMatrix("view", glm::value_ptr(view));
  shader->setMatrix("projection", glm::value_ptr(projection));

  for (int i = 0; i < tooltips.size(); i++) {
    Tooltip *t = tooltips[i];

    shader->setVec3("color", t->color);

    glm::mat4 model;
    model = glm::translate(model, t->position);

    shader->setMatrix("model", glm::value_ptr(model));

    mesh->draw();
  }
}

void TooltipRenderer::add(Tooltip *t) {
  tooltips.push_back(t);
}
