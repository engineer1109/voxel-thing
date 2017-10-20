#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <array>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <shader.hpp>
#include <chunk.hpp>
#include <mesh.hpp>
#include <utils.hpp>
#include <data.hpp>
#include <texture.hpp>
#include <world.hpp>
#include <block.hpp>

const float SCREEN_WIDTH=1600.0f;
const float SCREEN_HEIGHT=900.0f;

float lastTime;
float deltaTime;

float cameraSpeed = 5.0f;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

double lastMouseX = SCREEN_WIDTH/2;
double lastMouseY = SCREEN_HEIGHT/2;

float pitch = 0;
float yaw = 0;

bool firstMouse = true;

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    cameraPos += cameraSpeed * deltaTime * cameraFront;
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    cameraPos -= cameraSpeed * deltaTime * cameraFront;
  }

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
  }
}

void mouseCallback(GLFWwindow *window, double x, double y) {
  if (firstMouse) {
    lastMouseX = x;
    lastMouseY = y;

    firstMouse = false;
  }

  double xOffset = lastMouseX - x;
  double yOffset = lastMouseY - y;

  double sensitivity = 0.05;

  yaw  -= xOffset * sensitivity;
  pitch += yOffset * sensitivity;

  pitch = clamp(pitch, -89.0f, 89.0f);

  glm::vec3 front;

  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  cameraFront = glm::normalize(front);

  lastMouseX = x;
  lastMouseY = y;
}

bool mouseButton = false;
bool lastMouseButton = false;
bool justClicked = false;

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mode) {
  lastMouseButton = mouseButton;

  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    mouseButton = true;
  } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
    mouseButton = false;
  }
}

int main(void) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_FLOATING, GL_TRUE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "game", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();

    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cout << "Failed to initialise GLAD" << std::endl;

    return -1;
  }

  glEnable(GL_MULTISAMPLE);
  glEnable(GL_DEPTH_TEST);
  // glEnable(GL_CULL_FACE);

  // glCullFace(GL_BACK);  
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_WIDTH);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glfwSetCursorPosCallback(window, mouseCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);

  Shader blockLightingShader("shaders/lighting.vert", "shaders/block_lighting.frag");
  Shader hudShader("shaders/hud.vert", "shaders/hud.frag");
  Shader posGizmoShader("shaders/pos_gizmo.vert", "shaders/pos_gizmo.frag");

  stbi_set_flip_vertically_on_load(true);

  Texture dirtTexture("img/dirt.jpg");
  Texture crosshairTexture("img/crosshair.jpg");

  Mesh crosshairMesh(quad, { VEC3_VERTEX_ATTRIB, VEC3_VERTEX_ATTRIB, VEC2_VERTEX_ATTRIB });
  crosshairMesh.bind();

  Mesh posGizmoMesh(xyzLines, { VEC3_VERTEX_ATTRIB, VEC3_VERTEX_ATTRIB }, GL_LINES);
  posGizmoMesh.bind();

  World world;

  while (!glfwWindowShouldClose(window)) {
    deltaTime = (float) glfwGetTime() - lastTime;
    lastTime = (float) glfwGetTime();

    processInput(window);

    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(70.0f), SCREEN_WIDTH/SCREEN_HEIGHT, 0.1f, 100.0f);

    blockLightingShader.use();

    blockLightingShader.setMatrix("view", glm::value_ptr(view));
    blockLightingShader.setMatrix("projection", glm::value_ptr(projection));

    dirtTexture.use();

    for (int y = 0; y < WORLD_DEPTH; y++) {
      for (int x = 0; x < WORLD_WIDTH; x++) {
        std::shared_ptr<Chunk> chunk = world.chunks[y][x];

        glm::mat4 model;
        model = glm::translate(model, chunk->transform);

        blockLightingShader.setMatrix("model", glm::value_ptr(model));

        chunk->mesh->draw();
      }
    }

    posGizmoShader.use();

    glm::mat4 model;
    model = glm::translate(model, glm::vec3(1, 1, 1));

    posGizmoShader.setMatrix("view", glm::value_ptr(view));
    posGizmoShader.setMatrix("projection", glm::value_ptr(projection));
    posGizmoShader.setMatrix("model", glm::value_ptr(model));

    posGizmoMesh.draw();

    hudShader.use();

    glm::mat4 model;
    model = glm::scale(model, glm::vec3(0.02, 0.02, 0.02));

    hudShader.setMatrix("model", glm::value_ptr(model));
    crosshairTexture.use();
    crosshairMesh.draw();

    RayHit ray = world.ray(cameraPos, cameraFront);

    if (ray.didHit && (!lastMouseButton && mouseButton)) {
      world.chunks[ray.chunk.z][ray.chunk.x]->data[ray.block.y + 1][ray.block.z][ray.block.x] = SOLID;

      world.reloadChunks();
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
