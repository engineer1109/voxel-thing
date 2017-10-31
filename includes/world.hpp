#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <string>

#include <block.hpp>
#include <chunk.hpp>
#include <E/utils.hpp>
#include <block_database.hpp>

constexpr int WORLD_WIDTH = 3;
constexpr int WORLD_DEPTH = 3;

class World {
  public:
    World(std::string fname);

    std::vector<std::vector<std::shared_ptr<Chunk>>> chunks;

    void reloadChunks();

    E::RayHit ray(glm::vec3 origin, glm::vec3 direction);

    void save(std::string fname);

    BlockDatabase *blocks;
  private:
    bool saveExists(std::string fname);
};

#endif
