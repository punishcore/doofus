#include "Model.h"

#include "OBJLoader.h"

#include "../opengl/Shader.h"

Model::Model(
    const std::string& objPath,
    const std::string& texturePath
) {

    auto vertices = OBJLoader::load(objPath);

    mesh = std::make_unique<ModelMesh>(
        vertices.data(),
        vertices.size() * sizeof(float)
    );

    texture = std::make_unique<Texture>(texturePath);
}

void Model::draw(Shader& shader) {

    texture->bind(0);

    shader.setInt("tex", 0);

    mesh->draw();
}