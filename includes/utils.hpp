#ifndef UTILS_H
#define UTILS_H

#include <vector>

float clamp(float x, float upper, float lower);

float rgbToGl(float v);

int sum(std::vector<int>);

int randRange(int, int);

struct Index {
  int x;
  int y;
  int z;
};

#endif
