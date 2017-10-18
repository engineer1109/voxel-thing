#include "chunk.hpp"

#include <iostream>

Chunk::Chunk(glm::vec3 t) {
  generateLights();

  mesh = std::make_shared<ChunkMesh>(data, lightData);

  transform = t;
}

void Chunk::generateLights() {
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

  floodLightAt(2, 2, 2, 4);
}

void Chunk::floodLightAt(int xIndex, int yIndex, int zIndex, int r) {
  glm::vec3 origin(xIndex, yIndex, zIndex);

  float maxDistSqr = r*r;

  for (int y = yIndex - r; y < yIndex + r; y++) {
    for (int z = zIndex - r; z < zIndex + r; z++) {
      for (int x = xIndex - r; x < xIndex + r; x++) {
        if (y < 0 || z < 0 || x < 0) {
          continue;
        }

        if (y >= CHUNK_HEIGHT || z >= CHUNK_DEPTH || x >= CHUNK_WIDTH) {
          continue;
        }

        glm::vec3 pos(x, y, z);

        glm::vec3 temp = origin - pos;

        float distSqr = glm::dot(temp, temp);
        int strength = (int)((distSqr/maxDistSqr)*100.0f);

        lightData[y][z][x] = 100 - strength;
      }
    }
  }
}
