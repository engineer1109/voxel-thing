#ifndef WORLD_BUILDER_H
#define WORLD_BUILDER_H

#include <vector>
#include <glm/glm.hpp>

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

class WorldBuilder {
  public:
    WorldBuilder();

    std::vector<float> mesh();
    std::vector<float> addSide(glm::vec3 pos, BlockSide side);

  private:
    bool emptyToThe(glm::vec3, BlockSide side);

    std::vector<BlockSide> neededSidesAt(glm::vec3 index);

    int chunkData[CHUNK_HEIGHT][CHUNK_DEPTH][CHUNK_WIDTH] = {
    {
      { SOLID, SOLID, SOLID },
      { SOLID, EMPTY, SOLID },
      { SOLID, SOLID, SOLID }
    },
    {
      { SOLID, SOLID, SOLID },
      { SOLID, EMPTY, SOLID },
      { SOLID, SOLID, SOLID }
    },
    {
      { SOLID, SOLID, SOLID },
      { SOLID, EMPTY, SOLID },
      { SOLID, SOLID, SOLID }
    }
  };
};

#endif
