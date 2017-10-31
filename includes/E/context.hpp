#ifndef CONTEXT_H
#define CONTEXT_H

#include <GLFW/glfw3.h>

#include <E/render_manager.hpp>

namespace E {
  class Context {
    public:
      virtual void init() {};
      virtual void preFrame() {};
      virtual void render(RenderManager *renderer) {};
      virtual void postFrame() {};
  };
}

#endif
