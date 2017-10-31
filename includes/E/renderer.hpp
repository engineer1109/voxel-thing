#ifndef RENDERER_H
#define RENDERER_H

#include <E/view.hpp>

namespace E {
  class Renderer {
    public:
      virtual void preRender() {};
      virtual void render(View) {};
  };
}

#endif
