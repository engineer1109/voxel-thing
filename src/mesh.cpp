#include <mesh.hpp>

Mesh::Mesh(std::vector<float> d) {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  data = d;
  units = 6;

  bind();
}

Mesh::~Mesh() {
  /*
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  */
}

void Mesh::draw() {
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, data.size()/6);
}

void Mesh::bind() {
  glBindVertexArray(VAO);

  update();

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, units * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, units * sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);
}

void Mesh::update() {
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data.front(), GL_DYNAMIC_DRAW);
}
