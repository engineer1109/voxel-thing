#include "chunk.hpp"

Chunk::Chunk(glm::vec3 t) {
  mesh = std::make_shared<ChunkMesh>(data);

  transform = t;
}
