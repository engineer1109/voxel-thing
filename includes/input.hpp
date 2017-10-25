#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

#include <key_manager.hpp>

// should be accessed through the application.input.instance ptr.
class Input {
  public:
    Input();

    void update();

    KeyManager *keys;

    double mouseX;
    double mouseY;
    bool mousePrimaryPressed = false;

    static Input* instance();

    static void keyCallback(GLFWwindow*, int key, int scancode, int action, int mod);
    static void mouseButtonCallback(GLFWwindow*, int button, int action, int mod);
    static void mouseMovementCallback(GLFWwindow*, double x, double y);
  private:
    static Input* s_instance;
};

#endif
