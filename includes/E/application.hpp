#ifndef APPLICATION_H
#define APPLICATION_H

#include <GLFW/glfw3.h>

#include <E/context.hpp>
#include <E/state.hpp>

namespace E {
  class Application {
    public:
      Application(bool isVR);

      void loop();
    private:
      Context *context;
      GLFWwindow *window;

      State *state;

      float lastTime;

      static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
  };
};

#endif
