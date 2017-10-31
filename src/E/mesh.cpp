#include <E/mesh.hpp>

#include <iostream>

#include <E/utils.hpp>

E::Mesh::Mesh(std::vector<float> d, VertexAttribList val, unsigned int dm) {
  data = d;
  drawMode = dm;

  vertexAttribList = val;
  vertexAttribCount = sum(val);
  vertexAttribDataSize = sizeof(float);
}

E::Mesh::~Mesh() {
  // TODO: make this work
  /*
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  */
}

void E::Mesh::draw() {
  glBindVertexArray(VAO);
  glDrawArrays(drawMode, 0, data.size()/vertexAttribList.size());
}

void E::Mesh::bind() {
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

void E::Mesh::updateData(std::vector<float> d) {
  data = d;

  update();
}

void E::Mesh::update() {
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, data.size() * vertexAttribDataSize, &data.front(), GL_DYNAMIC_DRAW);
}
