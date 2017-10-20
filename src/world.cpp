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
  Index chunkIndex;
  Index blockIndex;

  glm::vec3 offset = {0.25f, 0, 0.25f};
  glm::vec3 i = origin + offset;

  direction /= 50;

  while(true) {
    chunkIndex = {
      (int) (i.x / CHUNK_WIDTH),
      0,
      (int) (i.z / CHUNK_DEPTH)
    };

    blockIndex = {
      ((int) i.x) % CHUNK_WIDTH,
      ((int) i.y) % CHUNK_HEIGHT,
      ((int) i.z) % CHUNK_WIDTH
    };

    if (chunkIndex.x < 0 || chunkIndex.z < 0) {
      // throw "this goes nowhere";

      return RayHit{false, chunkIndex, blockIndex};
    }

    if (chunkIndex.x >= WORLD_WIDTH || chunkIndex.z >= WORLD_DEPTH) {
      // throw "this also goes nowhere";

      return RayHit{false, chunkIndex, blockIndex};
    }

    std::shared_ptr<Chunk> chunk = chunks[chunkIndex.z][chunkIndex.x];

    int block = chunk->data[blockIndex.y][blockIndex.z][blockIndex.x];

    if (block == SOLID) {
      break;
    }

    i += direction;
  }

  // throw "fuck you";

  return RayHit{true, chunkIndex, blockIndex};
}
