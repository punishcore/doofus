#include "TextureArray.h"
#include "../../external/stb/stb_image.h"
#include <iostream>

TextureArray::TextureArray(
    const std::vector<std::string>& paths,
    int texSize,
    bool pixelated
)
{
    layerCount = (int)paths.size();

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D_ARRAY, id);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage3D(
        GL_TEXTURE_2D_ARRAY,
        0,
        GL_RGBA8,
        texSize,
        texSize,
        layerCount,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        nullptr
    );

    stbi_set_flip_vertically_on_load(true);

    int w, h, c;

    for (int i = 0; i < layerCount; i++)
    {
        unsigned char* data = stbi_load(paths[i].c_str(), &w, &h, &c, 4);

        if (!data)
        {
            std::cerr << "TextureArray: FAILED to load " << paths[i] << "\n";
            continue;
        }

        if (w != texSize || h != texSize)
        {
            std::cerr << "TextureArray: " << paths[i]
                      << " size mismatch (" << w << "x" << h
                      << " vs expected " << texSize << "x" << texSize << ")\n";
        }

        glTexSubImage3D(
            GL_TEXTURE_2D_ARRAY,
            0,
            0, 0, i,
            texSize,
            texSize,
            1,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            data
        );

        stbi_image_free(data);
    }

    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
}

void TextureArray::bind(int unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D_ARRAY, id);
}