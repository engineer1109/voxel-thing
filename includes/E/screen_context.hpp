#ifndef SCREEN_CONTEXT_H
#define SCREEN_CONTEXT_H

#include <GLFW/glfw3.h>

#include <E/camera.hpp>
#include <E/config.hpp>
#include <E/context.hpp>
#include <E/render_manager.hpp>
#include <E/view.hpp>

namespace E {
  class ScreenContext : public Context {
    public:
      ScreenContext(GLFWwindow* wind, Config *config);

      void preFrame();
      void render(RenderManager *renderer);
    private:
      View view();
  };
};

#endif
