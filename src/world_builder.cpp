#include "world_builder.hpp"

#include <iostream>

#include <glm/gtx/rotate_vector.hpp>

WorldBuilder::WorldBuilder() {}

std::vector<float> WorldBuilder::mesh() {
  std::vector<float> mesh;

  for (int y = 0; y < CHUNK_HEIGHT; y++) {
    for (int z = 0; z < CHUNK_DEPTH; z++) {
      for (int x = 0; x < CHUNK_WIDTH; x++) {
        int v = chunkData[y][z][x];
        if (v != SOLID) {
          continue;
        }

        glm::vec3 pos((float) x, (float) y, (float) z);

        std::vector<BlockSide> sides = neededSidesAt(pos);

        for (int i = 0; i < sides.size(); i++) {
          std::vector<float>face = addSide(pos, sides[i]);

          mesh.insert(mesh.end(), face.begin(), face.end());
        }
      }
    }
  }

  return mesh;
}

std::vector<float> WorldBuilder::addSide(glm::vec3 pos, BlockSide side) {
  std::vector<glm::vec3> face = {
    glm::vec3(0.5f,  0.5f, -0.5f), // top right
    glm::vec3(0.5f, -0.5f, -0.5f), // bottom right
    glm::vec3(-0.5f,  0.5f, -0.5f), // top left

    glm::vec3(0.5f, -0.5f, -0.5f), // bottom right
    glm::vec3(-0.5f, -0.5f, -0.5f), // bottom left
    glm::vec3(-0.5f,  0.5f, -0.5f) // top left
  };

  std::vector<glm::vec2> uvs = {
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 0.0f),

    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(0.0f, 0.0f)
  };

  glm::vec3 rotateAround;
  float rotateBy;

  switch(side) {
    case FRONT:
      rotateAround = glm::vec3(0.0f, 1.0f, 0.0f);
      rotateBy = 0.0f;

      break;
    case BACK:
      rotateAround = glm::vec3(0.0f, 1.0f, 0.0f);
      rotateBy = 180.0f;

      break;
    case LEFT:
      rotateAround = glm::vec3(0.0f, 1.0f, 0.0f);
      rotateBy = 270.0f;

      break;
    case RIGHT:
      rotateAround = glm::vec3(0.0f, 1.0f, 0.0f);
      rotateBy = 90.0f;

      break;
    case TOP:
      rotateAround = glm::vec3(1.0f, 0.0f, 0.0f);
      rotateBy = 90.0f;

      break;
    case BOTTOM:
      rotateAround = glm::vec3(1.0f, 0.0f, 0.0f);
      rotateBy = 270.0f;

      break;
    default:
      std::cout << "invalid side" << std::endl;

      throw "fuck you";
  }

  std::vector<float> verts;

  for (int i = 0; i < face.size(); i++) {
    glm::vec3 nvert = face[i];

    glm::vec3 rvert = glm::rotate(nvert, glm::radians(rotateBy), rotateAround);
    
    glm::vec3 vert = rvert + pos;

    // new vert
    verts.push_back(vert.x);
    verts.push_back(vert.y);
    verts.push_back(vert.z);

    glm::vec2 uv = uvs[i];

    // uv map
    verts.push_back(uv.x);
    verts.push_back(uv.y);
  }

  return verts;
}

bool WorldBuilder::emptyToThe(glm::vec3 index, BlockSide side) {
  switch (side) {
    case TOP:
      index.y += 1;

      break;
    case BOTTOM:
      index.y -= 1;

      break;
    case LEFT:
      index.x += 1;

      break;
    case RIGHT:
      index.x -= 1;

      break;
    case FRONT:
      index.z -= 1;

      break;
    case BACK:
      index.z += 1;

      break;
    default:
      throw "fuck this";
  }

  if (index.x < 0 || index.y < 0 || index.z < 0) {
    return true;
  }

  if (index.x > CHUNK_WIDTH - 1 || index.y > CHUNK_HEIGHT - 1 || index.z > CHUNK_DEPTH - 1) {
    return true;
  }

  return chunkData[(int)index.y][(int)index.z][(int)index.x] == EMPTY;
}

std::vector<BlockSide> WorldBuilder::neededSidesAt(glm::vec3 index) {
  std::vector<BlockSide> possibleSides = {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    FRONT,
    BACK
  };

  std::vector<BlockSide> sides;

  for (int i = 0; i < possibleSides.size(); i++) {
    BlockSide side = possibleSides[i];

    if (!emptyToThe(index, side)) {
      continue;
    }

    sides.push_back(side);
  }

  return sides;
}
