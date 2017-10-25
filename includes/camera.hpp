#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
  public:
    void update(float);
    void mouseCallback(double x, double y);

    glm::mat4 projectionMatrix();

    glm::vec3 pos = { 0, 0, 0 };
    glm::vec3 front = { 0, 0, -1 };
  private:
    double sensitivity = 0.05;

    glm::vec3 up = { 0.0f, 1.0f, 0.0f};

    double pitch = 0;
    double yaw = 0;

    double lastMouseX;
    double lastMouseY;
    
    bool firstMouse = false;
};

#endif
