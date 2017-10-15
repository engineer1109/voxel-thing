#ifndef BLOCK_H
#define BLOCK_H

enum BlockSide {
  TOP,
  BOTTOM,
  LEFT,
  RIGHT,
  FRONT,
  BACK
};

constexpr int CHUNK_WIDTH = 3;
constexpr int CHUNK_DEPTH = 3;
constexpr int CHUNK_HEIGHT = 3;

constexpr int EMPTY = 0;
constexpr int SOLID = 1;

#endif
