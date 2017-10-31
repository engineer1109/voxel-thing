#include "E/shader.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

E::Shader::Shader(const char* vertexPath, const char* fragmentPath) {
  std::cout << vertexPath << fragmentPath << std::endl;

  std::ifstream vp(vertexPath);
  std::ifstream fp(fragmentPath);

  auto vertexCode = std::string(std::istreambuf_iterator<char>(vp),
                                    (std::istreambuf_iterator<char>()));
  auto fragmentCode = std::string(std::istreambuf_iterator<char>(fp),
                                    (std::istreambuf_iterator<char>()));

  unsigned int vertexShader = compile(vertexCode.c_str(), GL_VERTEX_SHADER);
  unsigned int fragmentShader = compile(fragmentCode.c_str(), GL_FRAGMENT_SHADER);

  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);

  linkStatus();

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void E::Shader::use() {
  glUseProgram(ID);
}

void E::Shader::setInt(const std::string &name, int val) {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), val);
}

void E::Shader::setFloat(const std::string &name, float val) {
  glUniform1f(glGetUniformLocation(ID, name.c_str()), val);
}

void E::Shader::setMatrix(const std::string &name, float *val) {
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, val);
}

void E::Shader::setVec3(const std::string &name, float x, float y, float z) {
  glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void E::Shader::setVec3(const std::string &name, glm::vec3 v) {
  setVec3(name, v.x, v.y, v.z);
}

void E::Shader::setVec4(const std::string &name, float x, float y, float z, float w) {
  glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void E::Shader::setVec4(const std::string &name, glm::vec4 v) {
  setVec4(name, v.x, v.y, v.z, v.w);
}

unsigned int E::Shader::compile(const char* code, unsigned int type) {
  unsigned int shader = glCreateShader(type);

  glShaderSource(shader, 1, &code, NULL);
  
  glCompileShader(shader);

  compileStatus(shader);

  return shader;
}

void E::Shader::compileStatus(unsigned int shader) {
  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (success) {
    return;
  }

  glGetShaderInfoLog(shader, 512, NULL, infoLog);

  std::cout << "could not compile shader:" << infoLog << std::endl;
}

void E::Shader::linkStatus() {
  int success;
  char infoLog[512];
  glGetProgramiv(ID, GL_LINK_STATUS, &success);

  if (success) {
    return;
  }

  glGetShaderInfoLog(ID, 512, NULL, infoLog);

  std::cout << "could not link shader:" << infoLog << std::endl;
}
