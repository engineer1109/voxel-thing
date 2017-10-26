#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

class Shader {
  public:
    Shader(const char* vertexPath, const char* fragmentPath);

    void use();

    void setInt(const std::string &name, int val);
    void setFloat(const std::string &name, float val);
    void setMatrix(const std::string &name, float *val);
    void setVec3(const std::string &name, float x, float y, float z);
    void setVec3(const std::string &name, glm::vec3);
    void setVec4(const std::string &name, float x, float y, float z, float w);
    void setVec4(const std::string &name, glm::vec4);

    unsigned int ID;
  private:
    unsigned int compile(const char* code, unsigned int type);
    void compileStatus(unsigned int shader);
    void linkStatus();
};

#endif
