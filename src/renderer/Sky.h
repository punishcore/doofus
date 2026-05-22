#pragma once

#include "Shader.h"
#include <glad/gl.h>
#include <glm/glm.hpp>

class Sky {
public:
  Sky();
  ~Sky();

  void Init();

  void Render(const glm::vec3 &topColor, const glm::vec3 &horizonColor,
              const glm::vec3 &bottomColor);

public:
  GLuint VAO = 0;
  GLuint VBO = 0;
  Shader *shader = nullptr;

  void setupMesh();
};