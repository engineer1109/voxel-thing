#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>

class Shader {
  public:
    Shader(const char* vertexPath, const char* fragmentPath);

    void use();

    void setInt(const std::string &name, int val);
    void setFloat(const std::string &name, float val);

    unsigned int ID;
  private:
    unsigned int compile(const char* code, unsigned int type);
    void compileStatus(unsigned int shader);
    void linkStatus();
};

#endif
