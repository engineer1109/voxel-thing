#include <world.hpp>

#include <iostream>

#include <utils.hpp>

World::World() {
  for (int y = 0; y < WORLD_DEPTH; y++) {
    std::vector<std::shared_ptr<Chunk>> list;

    for (int x = 0; x < WORLD_WIDTH; x++) {
      glm::vec3 pos(WORLD_WIDTH*CHUNK_WIDTH/2 - x * CHUNK_WIDTH, 0, WORLD_DEPTH*CHUNK_DEPTH/2 - y * CHUNK_DEPTH);

      Index i = {
        x,
        0,
        y // y->z
      };

      list.push_back(std::make_shared<Chunk>(this, i, pos));
    }

    chunks.push_back(list);
  }

  for (int y = 0; y < WORLD_DEPTH; y++) {
    for (int x = 0; x < WORLD_WIDTH; x++) {
      std::shared_ptr<Chunk> chunk = chunks[y][x];

      chunk->ready();
    }
  }

  for (int y = 0; y < WORLD_DEPTH; y++) {
    for (int x = 0; x < WORLD_WIDTH; x++) {
      std::shared_ptr<Chunk> chunk = chunks[y][x];

      chunk->push();
    }
  }
}
