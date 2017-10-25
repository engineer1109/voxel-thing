#ifndef APPLICATION_H
#define APPLICATION_H

#include <GLFW/glfw3.h>

#include <game.hpp>

class Application {
  public:
    Application();

    void loop();
  private:
    GLFWwindow *window;

    Game *game;
    
    float lastTime;

    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
};

#endif
