#pragma once

#include "../Biome.h"

class PlainBiome : public Biome
{
public:

    const char* getName() override
    {
        return "Plains";
    }

    BlockType getTopBlock() override;
    BlockType getMiddleBlock() override;
    BlockType getBottomBlock() override;
};