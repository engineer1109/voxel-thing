#ifndef APPLICATION_H
#define APPLICATION_H

#include <GLFW/glfw3.h>

#include <E/context.hpp>
#include <E/state.hpp>

namespace E {
  class Application {
    public:
      Application();

      void loop();
    protected:
      void use(Context *ctx);

      State *state;
      GLFWwindow *window;
    private:
      Context *context;

      float lastTime;

      static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
  };
};

#endif
