float clamp(float x, float lower, float upper) {
  if (x > upper) {
    return upper;
  } else if (x < lower) {
    return lower;
  }

  return x;
}
