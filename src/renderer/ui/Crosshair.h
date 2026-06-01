#pragma once

#include <memory>

#include <glad/gl.h>

class Shader;
class Texture;

class Crosshair
{
public:

    Crosshair();

    ~Crosshair();

    void init();

    void render(
        int screenWidth,
        int screenHeight
    );

private:

    float size = 16.0f;

    GLuint vao = 0;
    GLuint vbo = 0;

    std::unique_ptr<Shader> shader;

    std::unique_ptr<Texture> texture;
};