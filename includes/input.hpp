#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

#include <key_manager.hpp>

// should be accessed through the application.input.instance ptr.
class Input {
  public:
    Input();

    void update();

    void endFrame();

    KeyManager *keys;

    // TODO: all mouse related functionality should be refactored out of here
    bool mouseMoved = false;

    double lastMouseX;
    double lastMouseY;
    double mouseX;
    double mouseY;

    double deltaMouseScrollX;
    double deltaMouseScrollY;

    bool lastMousePrimaryPressed = false;
    bool mousePrimaryPressed = false;

    bool mouseClicked();

    double deltaMouseX();
    double deltaMouseY();

    static Input* instance();

    static void keyCallback(GLFWwindow*, int key, int scancode, int action, int mod);
    static void mouseButtonCallback(GLFWwindow*, int button, int action, int mod);
    static void mouseMovementCallback(GLFWwindow*, double x, double y);
    static void mouseScrollCallback(GLFWwindow*, double xOffset, double yOffset);
  private:
    static Input* s_instance;
};

#endif
