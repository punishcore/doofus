#pragma once

#include <glad/gl.h>

class Mesh {
public:
    GLuint VAO;
    GLuint VBO;

    Mesh(float* vertices, unsigned int size);

    void draw();
};