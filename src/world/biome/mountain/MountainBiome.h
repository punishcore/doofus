#pragma once

#include "../Biome.h"

class MountainBiome : public Biome {
public:

const char* getName() override
{
    return "Mountain";
}

    BlockType getTopBlock() override;
    BlockType getMiddleBlock() override;
    BlockType getBottomBlock() override;
};