#include <mesh.hpp>

#include <iostream>

#include <utils.hpp>

Mesh::Mesh(std::vector<float> d, VertexAttribList val, unsigned int dm) {
  data = d;
  drawMode = dm;

  vertexAttribList = val;
  vertexAttribCount = sum(val);
  vertexAttribDataSize = sizeof(float);
}

Mesh::~Mesh() {
  /*
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  */
}

void Mesh::draw() {
  glBindVertexArray(VAO);
  glDrawArrays(drawMode, 0, data.size()/vertexAttribList.size());
}

void Mesh::bind() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  update();

  unsigned int total = 0;
  int attribListSize = vertexAttribCount * vertexAttribDataSize;

  for (int i = 0; i < vertexAttribList.size(); i++) {
    int attribSize = vertexAttribList[i];

    glVertexAttribPointer(i, attribSize, GL_FLOAT, GL_FALSE, attribListSize, (void*)total);
    glEnableVertexAttribArray(i);

    total += attribSize * vertexAttribDataSize;
  }
}

void Mesh::update() {
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, data.size() * vertexAttribDataSize, &data.front(), GL_DYNAMIC_DRAW);
}
