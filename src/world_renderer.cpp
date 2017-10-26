#include <world_renderer.hpp>

#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

WorldRenderer::WorldRenderer() {
  shader = new Shader("shaders/lighting.vert", "shaders/lighting.frag");
  texture = new Texture("img/dirt.jpg");
}

void WorldRenderer::render(Camera *camera, Config *config) {
  texture->use();
  shader->use();

  glm::mat4 view = camera->viewMatrix();
  glm::mat4 projection = camera->projectionMatrix();

  shader->setMatrix("view", glm::value_ptr(view));
  shader->setMatrix("projection", glm::value_ptr(projection));

  shader->setVec3("lightColor", glm::vec3(1.0, 1.0, 1.0));
  shader->setVec3("lightPos", glm::vec3(0, 2, 0));
  shader->setVec3("viewPos", *camera->position);

  for (int y = 0; y < WORLD_DEPTH; y++) {
    for (int x = 0; x < WORLD_WIDTH; x++) {
      std::shared_ptr<Chunk> chunk = world->chunks[y][x];

      glm::mat4 model;
      model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.5f));
      model = glm::translate(model, chunk->transform);

      shader->setMatrix("model", glm::value_ptr(model));
      chunk->mesh->draw();
    }
  }
}

void WorldRenderer::add(World *w) {
  if (world != NULL) {
    throw std::runtime_error("can't add a second world to the world renderer");
  }

  world = w;
}
