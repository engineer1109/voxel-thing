#include "shader.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
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

void Shader::use() {
  glUseProgram(ID);
}

unsigned int Shader::compile(const char* code, unsigned int type) {
  unsigned int shader = glCreateShader(type);

  glShaderSource(shader, 1, &code, NULL);
  
  glCompileShader(shader);

  compileStatus(shader);

  return shader;
}

void Shader::compileStatus(unsigned int shader) {
  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (success) {
    return;
  }

  glGetShaderInfoLog(shader, 512, NULL, infoLog);

  std::cout << "could not compile shader:" << infoLog << std::endl;
}

void Shader::linkStatus() {
  int success;
  char infoLog[512];
  glGetProgramiv(ID, GL_LINK_STATUS, &success);

  if (success) {
    return;
  }

  glGetShaderInfoLog(ID, 512, NULL, infoLog);

  std::cout << "could not link shader:" << infoLog << std::endl;
}
