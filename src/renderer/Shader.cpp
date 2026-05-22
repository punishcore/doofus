#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::string readFile(const char *path) {
  std::ifstream file(path);

  std::stringstream buffer;

  buffer << file.rdbuf();

  return buffer.str();
}

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
  std::string vertexCode = readFile(vertexPath);

  std::string fragmentCode = readFile(fragmentPath);

  const char *vertexSource = vertexCode.c_str();

  const char *fragmentSource = fragmentCode.c_str();

  GLuint vertex = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertex, 1, &vertexSource, nullptr);

  glCompileShader(vertex);

  GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragment, 1, &fragmentSource, nullptr);

  glCompileShader(fragment);

  id = glCreateProgram();

  glAttachShader(id, vertex);

  glAttachShader(id, fragment);

  glLinkProgram(id);

  glDeleteShader(vertex);

  glDeleteShader(fragment);
}

void Shader::use() { glUseProgram(id); }

void Shader::setInt(const std::string &name, int value) {
  glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setVec3(const std::string &name, const glm::vec3 &value) {
  glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y,
              value.z);
}