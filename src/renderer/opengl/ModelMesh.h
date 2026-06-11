#pragma once
#include <glad/gl.h>

class ModelMesh
{
public:
    GLuint VAO;
    GLuint VBO;
    int vertexCount;

    ModelMesh(float* vertices, unsigned int size);
    void draw();
};