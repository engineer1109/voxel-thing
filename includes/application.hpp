#ifndef APPLICATION_H
#define APPLICATION_H

#include <GLFW/glfw3.h>

#include <state.hpp>

class Application {
  public:
    Application();

    void loop();
  private:
    GLFWwindow *window;

    State *state;
    
    float lastTime;

    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
};

#endif
