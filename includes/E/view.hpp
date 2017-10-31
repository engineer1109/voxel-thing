#ifndef VIEW_H
#define VIEW_H

#include <glm/glm.hpp>

namespace E {
  struct View {
    View(glm::mat4 m) : viewProjMatrix(m) {};

    glm::mat4 viewProjMatrix;
  };
};

#endif
