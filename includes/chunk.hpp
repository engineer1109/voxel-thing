#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include <glm/glm.hpp>

#include <block.hpp>

class Chunk {
  public:
    Chunk(glm::vec3 pos=glm::vec3(0, 0, 0));

    std::vector<float> mesh();
  private:
    std::vector<float> addSide(glm::vec3 pos, BlockSide side);

    bool emptyToThe(glm::vec3, BlockSide side);

    std::vector<BlockSide> neededSidesAt(glm::vec3 index);

    int data[CHUNK_HEIGHT][CHUNK_DEPTH][CHUNK_WIDTH] = {
      {
        { SOLID, SOLID, SOLID },
        { SOLID, SOLID, SOLID },
        { SOLID, SOLID, SOLID }
      },
      {
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY }
      },
      {
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY }
      }
    };

  glm::vec3 transform;
};

#endif
