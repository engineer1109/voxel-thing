#ifndef RENDERER_H
#define RENDERER_H

#include <camera.hpp>
#include <config.hpp>

class Renderer {
  public:
    virtual void render(Camera *camera, Config *config) {};
};

#endif
