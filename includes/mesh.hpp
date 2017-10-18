#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <vector>

typedef std::vector<int> VertexAttribList;

const int VEC3_VERTEX_ATTRIB = 3;
const int VEC2_VERTEX_ATTRIB = 2;
const int F_VERTEX_ATTRIB = 1;

const VertexAttribList defaultVertexAttribList = {
  VEC3_VERTEX_ATTRIB, // vertex
  VEC3_VERTEX_ATTRIB  // normal
};

class Mesh {
  public:
		Mesh(std::vector<float> d, VertexAttribList val = defaultVertexAttribList);
		~Mesh();

    void bind();
    void draw();
  protected:
    void update();

    std::vector<float> data;
  private:
    unsigned int VAO;
    unsigned int VBO;

    VertexAttribList vertexAttribList;
    int vertexAttribCount;
    unsigned int vertexAttribDataSize;
};

#endif
