#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>

#include <block.hpp>
#include <chunk.hpp>
#include <utils.hpp>

constexpr int WORLD_WIDTH = 2;
constexpr int WORLD_DEPTH = 2;

class World {
  public:
    World();

    std::vector<std::vector<std::shared_ptr<Chunk>>> chunks;

    void reloadChunks();

    RayHit ray(glm::vec3 origin, glm::vec3 direction);
};

#endif
