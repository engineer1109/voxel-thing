#include <utils.hpp>

#include <random>

float clamp(float x, float lower, float upper) {
  if (x > upper) {
    return upper;
  } else if (x < lower) {
    return lower;
  }

  return x;
}

float rgbToGl(float v) {
    return v/255;
}

int sum(std::vector<int> v) {
  int total = 0;

  for (int i = 0; i < v.size(); i++) {
    total += v[i];
  }

  return total;
}

int randRange(int min, int max) {
  return min + (rand() % static_cast<int>(max - min + 1));
}
