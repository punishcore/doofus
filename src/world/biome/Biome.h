#pragma once

#include "../block/BlockType.h"
#include <string>

class Biome
{
public:
    virtual ~Biome() = default;

    virtual const char* getName() = 0;

    virtual BlockType getTopBlock() = 0;
    virtual BlockType getMiddleBlock() = 0;
    virtual BlockType getBottomBlock() = 0;
};