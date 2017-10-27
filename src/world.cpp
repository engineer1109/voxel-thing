#include <world.hpp>

#include <json.hpp>

#include <iostream>
#include <fstream>

#include <block.hpp>

using json = nlohmann::json;

World::World(std::string fname) {
  bool newWorld = false;

  json j;
  if (!saveExists(fname)) {
    newWorld = true;
  } else {
    std::ifstream file(fname.c_str());

    if (!file.good()) {
      throw "unable to access file";
    }

    j << file;
  }

  for (int y = 0; y < WORLD_DEPTH; y++) {
    std::vector<std::shared_ptr<Chunk>> list;

    for (int x = 0; x < WORLD_WIDTH; x++) {
      Index i = {
        x,
        0,
        y // y->z
      };

      glm::vec3 t(i.x*CHUNK_WIDTH, i.y*CHUNK_HEIGHT, i.z*CHUNK_DEPTH);

      if (newWorld) {
        list.push_back(std::make_shared<Chunk>(DEFAULT_CHUNK_DATA, this, i, t));
      } else {
        list.push_back(std::make_shared<Chunk>(j["world"][y][x],this, i, t));
      }
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
      return RayHit{false};
    }

    if (chunkIndex.x < 0 || chunkIndex.z < 0) {
      return RayHit{false};
    }

    if (chunkIndex.x >= WORLD_WIDTH || chunkIndex.z >= WORLD_DEPTH) {
      return RayHit{false};
    }

    std::shared_ptr<Chunk> chunk = chunks[chunkIndex.z][chunkIndex.x];

    int block = chunk->data[blockIndex.y][blockIndex.z][blockIndex.x];

    if (block == SOLID) {
      break;
    }

    i += direction;
  }

  return RayHit{true, chunkIndex, blockIndex, pChunkIndex, pBlockIndex, origin, i};
}

void World::save(std::string fname) {
  json j;

  std::vector<std::vector<ChunkData>> data;

  for (int y = 0; y < WORLD_DEPTH; y++) {
    std::vector<ChunkData> row;

    for (int x = 0; x < WORLD_WIDTH; x++) {
      std::shared_ptr<Chunk> chunk = chunks[y][x];

      row.push_back(chunk->data);
    }

    data.push_back(row);
  }

  j["world"] = data;

  std::ofstream file(fname.c_str());
  if (file.is_open()) {
    file << j;
    file.close();
  } else {
    std::cout << "Unable to open the mother fucking file" << std::endl;
  }
}

bool World::saveExists(std::string fname) {
  std::ifstream f(fname.c_str());

  return f.good();
}
