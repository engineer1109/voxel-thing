#ifndef RENDERER_H
#define RENDERER_H

#include <view.hpp>

class Renderer {
  public:
    virtual void preRender() {};
    virtual void render(View) {};
};

#endif
