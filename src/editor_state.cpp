#include <editor_state.hpp>

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <entity.hpp>
#include <data.hpp>

void EditorState::start() {
  worldShader = new Shader("shaders/default.vert", "shaders/default.frag");
  world = new World("world.json");

  cubeMesh = new Mesh(cube, { VEC3_VERTEX_ATTRIB, VEC3_VERTEX_ATTRIB });
  cubeMesh->bind();

  Cursor *cursor = new Cursor();
  add(cursor);
}

void EditorState::render() {
  glClearColor(0, 0, 0, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glm::mat4 view = camera.viewMatrix();
  glm::mat4 projection = camera.projectionMatrix();

  worldShader->use();

  worldShader->setMatrix("view", glm::value_ptr(view));
  worldShader->setMatrix("projection", glm::value_ptr(projection));

  for (int y = 0; y < WORLD_DEPTH; y++) {
    for (int x = 0; x < WORLD_WIDTH; x++) {
      std::shared_ptr<Chunk> chunk = world->chunks[y][x];

      glm::mat4 model;
      model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.5f));
      model = glm::translate(model, chunk->transform);

      worldShader->setMatrix("model", glm::value_ptr(model));
      chunk->mesh->draw();
    }
  }

  glm::vec3 p = camera.screenToDirection(glm::vec2(300, 300));

  glm::mat4 model;
  model = glm::translate(model, *camera.position + (p*10.0f));
  worldShader->setMatrix("model", glm::value_ptr(model));

  cubeMesh->draw();
}
