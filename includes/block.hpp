#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

enum BlockSide {
  TOP,
  BOTTOM,
  LEFT,
  RIGHT,
  FRONT,
  BACK
};

constexpr int CHUNK_WIDTH = 10;
constexpr int CHUNK_DEPTH = 10;
constexpr int CHUNK_HEIGHT = 10;

typedef std::vector<std::vector<std::vector<int>>> ChunkData;

constexpr int EMPTY = 0;
constexpr int SOLID = 1;
constexpr int LIGHT = 2;

#endif
