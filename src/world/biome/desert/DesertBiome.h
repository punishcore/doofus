#pragma once
#include "../Biome.h"

class DesertBiome : public Biome {
public:
    int getBaseHeight(int worldX, int worldZ) override;

    BlockType getTopBlock() override;
    BlockType getMiddleBlock() override;
    BlockType getBottomBlock() override;
};