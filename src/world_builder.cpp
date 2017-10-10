#include "world_builder.hpp"

std::vector<float> WorldBuilder::mesh() {
  // take input: 3d array
  float chunkData[CHUNK_WIDTH][CHUNK_DEPTH][CHUNK_HEIGHT] = {
    {
      { 1, 1, 1 },
      { 1, 0, 1 },
      { 1, 1, 1 }
    },
    {
      { 1, 1, 1 },
      { 1, 0, 1 },
      { 1, 1, 1 }
    },
    {
      { 1, 1, 1 },
      { 1, 0, 1 },
      { 1, 1, 1 }
    }
  };

  std::vector<float> mesh;

  for (int x = 0; x < CHUNK_WIDTH; x++) {
    for (int z = 0; z < CHUNK_DEPTH; z++) {
      for (int y = 0; y < CHUNK_HEIGHT; y++) {
        std::vector<float> cube = {
          // x   y      z       
          x + -0.5f, y + -0.5f, z + -0.5f,  0.0f, 0.0f,
          x + 0.5f, y + -0.5f, z + -0.5f,  1.0f, 0.0f,
          x + 0.5f,  y + 0.5f, z + -0.5f,  1.0f, 1.0f,
          x + 0.5f, y + 0.5f, z + -0.5f,  1.0f, 1.0f,
          x + -0.5f, y + 0.5f, z + -0.5f,  0.0f, 1.0f,
          x + -0.5f, y + -0.5f, z + -0.5f,  0.0f, 0.0f,

          x + -0.5f, y + -0.5f,  z + 0.5f,  0.0f, 0.0f,
          x + 0.5f, y + -0.5f,  z + 0.5f,  1.0f, 0.0f,
          x + 0.5f,  y + 0.5f,  z + 0.5f,  1.0f, 1.0f,
          x + 0.5f, y +  0.5f,  z + 0.5f,  1.0f, 1.0f,
          x + -0.5f, y +  0.5f,  z + 0.5f,  0.0f, 1.0f,
          x + -0.5f, y + -0.5f,  z + 0.5f,  0.0f, 0.0f,

          x + -0.5f, y +  0.5f,  z + 0.5f,  1.0f, 0.0f,
          x + -0.5f,  y + 0.5f, z + -0.5f,  1.0f, 1.0f,
          x + -0.5f, y + -0.5f, z + -0.5f,  0.0f, 1.0f,
          x + -0.5f, y + -0.5f, z + -0.5f,  0.0f, 1.0f,
          x + -0.5f, y + -0.5f,  z + 0.5f,  0.0f, 0.0f,
          x + -0.5f, y +  0.5f,  z + 0.5f,  1.0f, 0.0f,

          x + 0.5f, y +  0.5f,  z + 0.5f,  1.0f, 0.0f,
          x + 0.5f,  y + 0.5f, z + -0.5f,  1.0f, 1.0f,
          x + 0.5f, y + -0.5f, z + -0.5f,  0.0f, 1.0f,
          x + 0.5f, y + -0.5f, z + -0.5f,  0.0f, 1.0f,
          x + 0.5f, y + -0.5f,  z + 0.5f,  0.0f, 0.0f,
          x + 0.5f,  y + 0.5f,  z + 0.5f,  1.0f, 0.0f,

          x + -0.5f, y + -0.5f, z + -0.5f,  0.0f, 1.0f,
          x + 0.5f, y + -0.5f, z + -0.5f,  1.0f, 1.0f,
          x + 0.5f, y + -0.5f,  z + 0.5f,  1.0f, 0.0f,
          x + 0.5f, y + -0.5f,  z + 0.5f,  1.0f, 0.0f,
          x + -0.5f, y + -0.5f,  z + 0.5f,  0.0f, 0.0f,
          x + -0.5f, y + -0.5f, z + -0.5f,  0.0f, 1.0f,

          x + -0.5f,  y + 0.5f, z + -0.5f,  0.0f, 1.0f,
          x + 0.5f,  y + 0.5f, z + -0.5f,  1.0f, 1.0f,
          x + 0.5f,  y + 0.5f,  z + 0.5f,  1.0f, 0.0f,
          x + 0.5f,  y + 0.5f,  z + 0.5f,  1.0f, 0.0f,
          x + -0.5f,  y + 0.5f,  z + 0.5f,  0.0f, 0.0f,
          x +-0.5f,  y + 0.5f, z + -0.5f,  0.0f, 1.0f
        };

        mesh.insert(mesh.end(), cube.begin(), cube.end());
      }
    }
  }

  // produce output: vertex list
  return mesh;
}
