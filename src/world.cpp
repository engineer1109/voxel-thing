#include <world.hpp>

#include <iostream>

#include <block.hpp>

World::World() {
  for (int y = 0; y < WORLD_DEPTH; y++) {
    std::vector<std::shared_ptr<Chunk>> list;

    for (int x = 0; x < WORLD_WIDTH; x++) {
      Index i = {
        x,
        0,
        y // y->z
      };

      list.push_back(std::make_shared<Chunk>(this, i));
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

void World::reloadChunks() {
  for (int y = 0; y < WORLD_DEPTH; y++) {
    for (int x = 0; x < WORLD_WIDTH; x++) {
      std::shared_ptr<Chunk> chunk = chunks[y][x];

      chunk->ready();
    }
  }

  for (int y = 0; y < WORLD_DEPTH; y++) {
    for (int x = 0; x < WORLD_WIDTH; x++) {
      std::shared_ptr<Chunk> chunk = chunks[y][x];

      chunk->refresh();
    }
  }
}

RayHit World::ray(glm::vec3 origin, glm::vec3 direction) {
  Index pChunkIndex;
  Index pBlockIndex;
  Index chunkIndex;
  Index blockIndex;

  glm::vec3 i = origin;

  direction /= 25;

  while(true) {
    pChunkIndex = chunkIndex;
    pBlockIndex = blockIndex;

    chunkIndex = {
      (int) (floor(i.x) / CHUNK_WIDTH),
      0,
      (int) (floor(i.z) / CHUNK_DEPTH)
    };

    blockIndex = {
      ((int) floor(i.x)) % CHUNK_WIDTH,
      ((int) floor(i.y)) % CHUNK_HEIGHT,
      ((int) floor(i.z)) % CHUNK_WIDTH
    };

    if (blockIndex.x < 0 || blockIndex.y < 0 || blockIndex.z < 0) {
      return RayHit{false, chunkIndex, blockIndex};
    }

    if (chunkIndex.x < 0 || chunkIndex.z < 0) {
      return RayHit{false, chunkIndex, blockIndex};
    }

    if (chunkIndex.x >= WORLD_WIDTH || chunkIndex.z >= WORLD_DEPTH) {
      return RayHit{false, chunkIndex, blockIndex};
    }

    std::shared_ptr<Chunk> chunk = chunks[chunkIndex.z][chunkIndex.x];

    int block = chunk->data[blockIndex.y][blockIndex.z][blockIndex.x];

    if (block == SOLID) {
      break;
    }

    i += direction;
  }

  return RayHit{true, pChunkIndex, pBlockIndex, origin, i};
}
