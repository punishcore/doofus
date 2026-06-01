#pragma once
#include <glad/gl.h>
#include <vector>
#include <string>

class TextureArray {
public:
    GLuint id;
    int layerCount;

    TextureArray(const std::vector<std::string>& paths, int texSize, bool pixelated = true);
    void bind(int unit = 0);
};