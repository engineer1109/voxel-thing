#ifndef CHUNK_MESH_H
#define CHUNK_MESH_H

#include <glm/glm.hpp>

#include <mesh.hpp>
#include <block.hpp>
#include <block_database.hpp>

const VertexAttribList chunkMeshVertexAttribList = {
  VEC3_VERTEX_ATTRIB, // vertex
  VEC2_VERTEX_ATTRIB, // uv coords
  VEC3_VERTEX_ATTRIB, // normal
  F_VERTEX_ATTRIB,     // light strength
  VEC4_VERTEX_ATTRIB // block color tint
};

class ChunkMesh : public Mesh {
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
