#include <editor_state.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <entity.hpp>

void EditorState::start() {
  worldShader = new Shader("shaders/default.vert", "shaders/default.frag");
  world = new World("world.json");

  Cursor *cursor = new Cursor();
  add(cursor);
}

void EditorState::render() {
  glClearColor(0, 0, 0, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  worldShader->use();

  glm::mat4 view = camera.viewMatrix();
  glm::mat4 projection = glm::perspective(glm::radians(95.0f), SCREEN_WIDTH/SCREEN_HEIGHT, 0.1f, 100.0f);

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
}
