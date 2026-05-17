#pragma once

#include <string>
#include <glad/gl.h>

class Shader {
public:
    GLuint id;

    Shader(
        const char* vertexSource,
        const char* fragmentSource
    );

    void use();
};