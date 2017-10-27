#include "chunk.hpp"

#include <world.hpp>

#include <iostream>

Chunk::Chunk(ChunkData cd, World *w, Index i, glm::vec3 t) {
  data = cd;
  world = w;
  transform = t;
  index = i;

  initLights();
}

void Chunk::ready() {
  generateLights();
}

void Chunk::refresh() {
  mesh->generate(data, lightData);
  mesh->update();
}

void Chunk::push() {
  mesh = std::make_shared<ChunkMesh>(data, lightData);

  mesh->bind();
}

ChunkData Chunk::defaultData() {
  ChunkData cd;

  for (int y = 0; y < CHUNK_HEIGHT; y++) {
    std::vector<std::vector<int>> column;
    for (int z = 0; z < CHUNK_DEPTH; z++) {
      std::vector<int> row;
      for (int x = 0; x < CHUNK_WIDTH; x++) {
        int v = EMPTY;

        if (y == 0) v = SOLID;

        row.push_back(v);
      }

      column.push_back(row);
    }

    cd.push_back(column);
  }

  return cd;
}

void Chunk::initLights() {
  lightData.clear();

  for (int y = 0; y < CHUNK_HEIGHT; y++) {
    std::vector<std::vector<int>> col;

    for (int z = 0; z < CHUNK_DEPTH; z++) {
      std::vector<int> vals;

      for (int x = 0; x < CHUNK_WIDTH; x++) {
        vals.push_back(0);
      }

      col.push_back(vals);
    }

    lightData.push_back(col);
  }
}

void Chunk::generateLights() {
  //floodLightAt(randRange(0, 9), 2, randRange(0, 9), randRange(2, 9));
  floodLightAt(2, 2, 2, 4);
  floodLightAt(6, 2, 6, 4);
}

void Chunk::floodLightAt(int xIndex, int yIndex, int zIndex, int r) {
  glm::vec3 origin(xIndex, yIndex, zIndex);

  float maxDistSqr = r*r;

  for (int y = yIndex - r; y < yIndex + r; y++) {
    for (int z = zIndex - r; z < zIndex + r; z++) {
      for (int x = xIndex - r; x < xIndex + r; x++) {
        Index chunkIndex = index;
        Index blockIndex = {x, y, z};

        if (x < 0) {
          chunkIndex.x += 1;
          blockIndex.x = x + CHUNK_WIDTH;
        }

        if (x >= CHUNK_WIDTH) {
          chunkIndex.x -= 1;
          blockIndex.x = x - CHUNK_WIDTH;
        }

        if (z < 0) {
          chunkIndex.z += 1;
          blockIndex.z = z + CHUNK_DEPTH;
        }

        if (z >= CHUNK_DEPTH) {
          chunkIndex.z -= 1;
          blockIndex.z = z - CHUNK_DEPTH;
        }

        if (y < 0 || y >= CHUNK_HEIGHT) {
          continue;
        }

        if (chunkIndex.x < 0 || chunkIndex.z < 0) {
          continue;
        }

        if (chunkIndex.x >= WORLD_WIDTH || chunkIndex.z >= WORLD_DEPTH) {
          continue;
        }

        glm::vec3 pos(x, y, z);
        glm::vec3 temp = origin - pos;
        float distSqr = glm::dot(temp, temp);

        if (distSqr > maxDistSqr) {
          continue;
        }

        float strength = pow(distSqr/maxDistSqr, 2);
        int v = 100 - (int)(strength*100.0f);

        std::shared_ptr<Chunk> chunk = world->chunks[chunkIndex.z][chunkIndex.x];
        if (chunk->data[blockIndex.y][blockIndex.z][blockIndex.x] == SOLID) {
          continue;
        }

        if (chunk->lightData[blockIndex.y][blockIndex.z][blockIndex.x] > v) {
          continue;
        }

        chunk->lightData[blockIndex.y][blockIndex.z][blockIndex.x] = v;
      }
    }
  }
}
