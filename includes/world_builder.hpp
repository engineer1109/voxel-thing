#ifndef WORLD_BUILDER_H
#define WORLD_BUILDER_H

#include <vector>

class WorldBuilder {
  const int CHUNK_WIDTH = 3;
  const int CHUNK_DEPTH = 3;
  const int CHUNK_HEIGHT = 3;

  public:
    std::vector<float> mesh();
};

#endif
