#ifndef SCREEN_CONTEXT_H
#define SCREEN_CONTEXT_H

#include <GLFW/glfw3.h>

#include <context.hpp>
#include <render_manager.hpp>
#include <camera.hpp>
#include <view.hpp>

class ScreenContext : public Context {
  public:
    ScreenContext(Camera *cam, GLFWwindow* wind);

    void preFrame();
    void render(RenderManager *renderer);
  private:
    View view();

    Camera *camera;
};

#endif
