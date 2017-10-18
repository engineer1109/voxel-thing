#include <world.hpp>

World::World() {
  for (int y = 0; y < WORLD_DEPTH; y++) {
    std::vector<Chunk> list;

    for (int x = 0; x < WORLD_WIDTH; x++) {
      glm::vec3 pos(WORLD_WIDTH*CHUNK_WIDTH/2 - x * CHUNK_WIDTH, 0, WORLD_DEPTH*CHUNK_DEPTH/2 - y * CHUNK_DEPTH);

      list.push_back(Chunk(pos));
    }

    chunks.push_back(list);
  }
}
