#pragma once

#include "../block/BlockType.h"

class Biome {
public:
    virtual ~Biome() = default;

    virtual int getBaseHeight(int worldX, int worldZ) = 0;

    virtual BlockType getTopBlock() = 0;
    virtual BlockType getMiddleBlock() = 0;
    virtual BlockType getBottomBlock() = 0;
};