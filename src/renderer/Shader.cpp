#include "Shader.h"
#include <iostream>

Shader::Shader(
    const char* vertexSource,
    const char* fragmentSource
)
{
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(
        vertex,
        1,
        &vertexSource,
        nullptr
    );

    glCompileShader(vertex);

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(
        fragment,
        1,
        &fragmentSource,
        nullptr
    );

    glCompileShader(fragment);

    id = glCreateProgram();

    glAttachShader(id, vertex);
    glAttachShader(id, fragment);

    glLinkProgram(id);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(id);
}