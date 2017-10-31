#include <E/utils.hpp>

#include <random>

float E::clamp(float x, float lower, float upper) {
  if (x > upper) {
    return upper;
  } else if (x < lower) {
    return lower;
  }

  return x;
}

float E::rgbToGl(float v) {
    return v/255;
}

int E::sum(std::vector<int> v) {
  int total = 0;

  for (int i = 0; i < v.size(); i++) {
    total += v[i];
  }

  return total;
}

int E::randRange(int min, int max) {
  return min + (rand() % static_cast<int>(max - min + 1));
}
