#ifndef WORLD_BUILDER_H
#define WORLD_BUILDER_H

#include <vector>
#include <glm/glm.hpp>

enum BlockSide {
  TOP,
  BOTTOM,
  LEFT,
  RIGHT,
  FRONT,
  BACK
};

class WorldBuilder {
  const int CHUNK_WIDTH = 3;
  const int CHUNK_DEPTH = 3;
  const int CHUNK_HEIGHT = 3;

  const float UNIT_SIZE = 1;

  public:
    std::vector<float> mesh();
    std::vector<float> addSide(glm::vec3 pos, BlockSide side);
};

#endif
