#pragma once

#include "../opengl/Mesh.h"
#include "../opengl/Texture.h"

#include <memory>

class Shader;

class Model {
public:

    std::unique_ptr<Mesh> mesh;
    std::unique_ptr<Texture> texture;

    Model(
        const std::string& objPath,
        const std::string& texturePath
    );

    void draw(Shader& shader);
};