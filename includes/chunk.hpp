#ifndef CHUNK_H
#define CHUNK_H

#include <memory>
#include <vector>

#include <E/utils.hpp>
#include <block.hpp>
#include <chunk_mesh.hpp>

class World;

class Chunk {
  public:
    // The `z` component of the index is not used since the World is a 2D array of chunks.
    Chunk(ChunkData cd, World *w, E::Index i, glm::vec3 t);

    ChunkData data;
    std::shared_ptr<ChunkMesh> mesh;
    glm::vec3 transform;

    void ready();
    void push();
    void refresh();

    static ChunkData defaultData();
  private:
    E::Index index;
    World *world;

    ChunkData lightData = {};

    void initLights();
    void generateLights();
    void floodLightAt(int, int, int, int=5);
};

#endif
