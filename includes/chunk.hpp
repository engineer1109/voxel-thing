#ifndef CHUNK_H
#define CHUNK_H

#include <memory>
#include <vector>

#include <block.hpp>

#include <chunk_mesh.hpp>

class Chunk {
  public:
    Chunk(glm::vec3 t = glm::vec3());

    std::shared_ptr<ChunkMesh> mesh;

    glm::vec3 transform;
  private:
    ChunkData data = {
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
};

#endif
