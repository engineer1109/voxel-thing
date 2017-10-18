#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include <block.hpp>
#include <chunk.hpp>

constexpr int WORLD_WIDTH = 3;
constexpr int WORLD_DEPTH = 3;

class World {
  public:
    World();

    std::vector<std::vector<Chunk>> chunks;
};

#endif
