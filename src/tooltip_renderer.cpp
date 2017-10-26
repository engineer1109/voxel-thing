#include <tooltip_renderer.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <data.hpp>

TooltipRenderer::TooltipRenderer() {
  shader = new Shader("shaders/default.vert", "shaders/default.frag");
  mesh = new Mesh(cube, { VEC3_VERTEX_ATTRIB, VEC3_VERTEX_ATTRIB });
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

    glm::mat4 model;
    model = glm::translate(model, t->position);

    shader->setMatrix("model", glm::value_ptr(model));

    mesh->draw();
  }
}

void TooltipRenderer::add(Tooltip *t) {
  tooltips.push_back(t);
}
