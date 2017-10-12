#include "world_builder.hpp"

#include <iostream>

#include <glm/gtx/rotate_vector.hpp>

std::vector<float> WorldBuilder::mesh() {
  glm::vec3 pos(0.0f, 0.0f, 0.0f);

  std::vector<float> mesh;

  std::vector<BlockSide> sides = {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    FRONT,
    BACK
  };

  for (int i = 0; i < sides.size(); i++) {
    std::vector<float>face = addSide(pos, sides[i]);
    mesh.insert(mesh.end(), face.begin(), face.end());
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

    // uv map
    verts.push_back(0.0f);
    verts.push_back(1.0f);
  }

  return verts;
}
