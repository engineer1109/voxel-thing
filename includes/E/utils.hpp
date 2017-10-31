#ifndef UTILS_H
#define UTILS_H

#include <glm/glm.hpp>
#include <vector>

namespace E {
  const glm::vec3 UP = { 0.0f, 1.0f, 0.0f };

  float clamp(float x, float upper, float lower);

  float rgbToGl(float v);

  int sum(std::vector<int>);

  int randRange(int, int);

  struct Index {
    int x;
    int y;
    int z;
  };

  struct RayHit {
    bool didHit;

    Index chunk;
    Index block;

    Index prevChunk;
    Index prevBlock;

    glm::vec3 start;
    glm::vec3 end;
  };

}

#endif
