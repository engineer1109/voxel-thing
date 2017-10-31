#ifndef CHUNK_MESH_H
#define CHUNK_MESH_H

#include <glm/glm.hpp>

#include <E/mesh.hpp>

#include <block.hpp>
#include <block_database.hpp>

const E::VertexAttribList chunkMeshVertexAttribList = {
  E::VEC3_VERTEX_ATTRIB, // vertex
  E::VEC2_VERTEX_ATTRIB, // uv coords
  E::VEC3_VERTEX_ATTRIB, // normal
  E::F_VERTEX_ATTRIB,     // light strength
  E::VEC4_VERTEX_ATTRIB // block color tint
};

class ChunkMesh : public E::Mesh {
  public:
    ChunkMesh(BlockDatabase *bd, ChunkData cd, ChunkData ld);

    void generate(ChunkData cd, ChunkData ld);
  private:
    std::vector<float> generateFace(glm::vec3, BlockSide, BlockType);
    std::vector<BlockSide> neededSidesAt(glm::vec3);
    bool emptyToThe(glm::vec3, BlockSide);

    float lightStrengthAt(glm::vec3, BlockSide);

    ChunkData chunkData;
    ChunkData lightData;

    BlockDatabase *blocks;
};

#endif
