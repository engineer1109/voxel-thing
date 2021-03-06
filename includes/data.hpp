#ifndef DATA_H
#define DATA_H

std::vector<float> xyzLines = {
  0.0f, 0.0f, 0.0f, 0.2f, 0.0f, 0.0f,
  10.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 0.0f, 0.2f, 0.0f,
  0.0f, 10.0f, 0.0f, 0.0f, 1.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.2f,
  0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 1.0f
};

std::vector<float> quad = {
  1.0f,  1.0f, -1.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
  1.0f, -1.0f, -1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
  -1.0f,  1.0f, -1.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // top left 
  1.0f, -1.0f, -1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
  -1.0f, -1.0f, -1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
  -1.0f,  1.0f, -1.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

// this cube does not have the correct winding order.
// have had to disable face culling.
std::vector<float> cube = {
  // pos                norm
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
  0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
  -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
  0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
  0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

#endif
