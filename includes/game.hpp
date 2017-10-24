#ifndef GAME_H
#define GAME_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <key_manager.hpp>
#include <shader.hpp>
#include <texture.hpp>
#include <mesh.hpp>
#include <world.hpp>
#include <camera.hpp>

const float SCREEN_WIDTH=1600.0f;
const float SCREEN_HEIGHT=900.0f;

class Game {
  public:
    Game(GLFWwindow *wind);

    void update(float deltaTime);
    void render();
  private:
    Shader *defaultShader;
    Shader *lightingShader;
    Shader *hudShader;
    Shader *gizmoShader;

    Texture *dirtTexture;
    Texture *crosshairTexture;

    Mesh *crosshairMesh;
    Mesh *posGizmoMesh;
    Mesh *rayLineMesh;
    Mesh *lightMesh;

    World *world;

    glm::vec3 lightPos;
    glm::vec3 lightColor;

    static void mouseCallback(GLFWwindow *window, double x, double y);
};

#endif
