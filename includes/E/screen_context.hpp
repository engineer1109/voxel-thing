#ifndef SCREEN_CONTEXT_H
#define SCREEN_CONTEXT_H

#include <GLFW/glfw3.h>

#include <E/context.hpp>
#include <E/render_manager.hpp>
#include <E/camera.hpp>
#include <E/view.hpp>

namespace E {
  class ScreenContext : public Context {
    public:
      ScreenContext(Camera *cam, GLFWwindow* wind);

      void preFrame();
      void render(RenderManager *renderer);
    private:
      View view();

      Camera *camera;
  };
}

#endif
