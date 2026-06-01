#pragma once

#include <glad/gl.h>

#include <string>

class Texture {
public:
  GLuint id;

  Texture(
      const std::string &path,
      bool pixelated = true);

  void bind(int unit = 0);
};