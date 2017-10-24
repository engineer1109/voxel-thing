#include <game.hpp>

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <data.hpp>

extern KeyManager KEYS;
Camera *camera;

Game::Game(GLFWwindow *wind) {
  glfwSetCursorPosCallback(wind, mouseCallback);

  defaultShader = new Shader("shaders/default.vert", "shaders/default.frag");
  lightingShader = new Shader("shaders/lighting.vert", "shaders/lighting.frag");
  hudShader = new Shader("shaders/hud.vert", "shaders/hud.frag");
  gizmoShader = new Shader("shaders/pos_gizmo.vert", "shaders/pos_gizmo.frag");

  dirtTexture = new Texture("img/ground.jpeg");
  crosshairTexture = new Texture("img/crosshair.jpg");

  posGizmoMesh = new Mesh(xyzLines, { VEC3_VERTEX_ATTRIB, VEC3_VERTEX_ATTRIB }, GL_LINES);
  posGizmoMesh->bind();

  rayLineMesh = new Mesh(std::vector<float>(), { VEC3_VERTEX_ATTRIB, VEC3_VERTEX_ATTRIB }, GL_LINES);
  rayLineMesh->bind();

  lightMesh = new Mesh(cube, { VEC3_VERTEX_ATTRIB, VEC3_VERTEX_ATTRIB});
  lightMesh->bind();

  world = new World("world.json");
  camera = new Camera();

  lightPos = glm::vec3(0, 2, 0);
  lightColor = glm::vec3(0.5, 0.2, 0.7);
}

void Game::update(float dt) {
  camera->update(dt);

  std::cout << "fuck you" << std::endl;
  std::cout << "cpx:" << camera->pos.x << std::endl;
  std::cout << "cpy:" << camera->pos.y << std::endl;
  std::cout << "cpz:" << camera->pos.z << std::endl;
}

void Game::render() {
  glClearColor(0, 0, 0, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glm::mat4 view = camera->projectionMatrix();

  glm::mat4 projection;
  projection = glm::perspective(glm::radians(95.0f), SCREEN_WIDTH/SCREEN_HEIGHT, 0.1f, 100.0f);

  lightingShader->use();

  lightingShader->setMatrix("view", glm::value_ptr(view));
  lightingShader->setMatrix("projection", glm::value_ptr(projection));

  lightingShader->setVec3("lightColor", lightColor);
  lightingShader->setVec3("lightPos", lightPos);
  lightingShader->setVec3("viewPos", camera->pos);

  dirtTexture->use();

  for (int y = 0; y < WORLD_DEPTH; y++) {
    for (int x = 0; x < WORLD_WIDTH; x++) {
      std::shared_ptr<Chunk> chunk = world->chunks[y][x];

      glm::mat4 model;
      model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.5f));
      model = glm::translate(model, chunk->transform);

      lightingShader->setMatrix("model", glm::value_ptr(model));

      chunk->mesh->draw();
    }
  }
}

void Game::mouseCallback(GLFWwindow *window, double x, double y) {
  camera->mouseCallback(x, y);
}
