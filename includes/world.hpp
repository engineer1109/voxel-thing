#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>

#include <block.hpp>
#include <chunk.hpp>

constexpr int WORLD_WIDTH = 3;
constexpr int WORLD_DEPTH = 3;

class World {
  public:
    World();

    std::vector<std::vector<std::shared_ptr<Chunk>>> chunks;
};

#endif
