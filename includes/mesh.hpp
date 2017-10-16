#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <vector>

class Mesh {
  public:
		Mesh(std::vector<float> d);
		~Mesh();

    void draw();
  protected:
    void update();

    std::vector<float> data;
  private:
    unsigned int VAO;
    unsigned int VBO;

    int units;

    void bind();
};

#endif
