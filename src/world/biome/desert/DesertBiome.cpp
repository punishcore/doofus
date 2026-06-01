#include "DesertBiome.h"
#include "../../noise/FBMNoise.h"
#include "../../../core/Setting.h"
#include <cmath>

int DesertBiome::getBaseHeight(int worldX, int worldZ) {
    float n =
        FBMNoise::generate(
    worldX,
    worldZ,
    5,
    0.5f,
    0.008f,
    Setting::seed
);

    return 25 + (int)(n * 5.0f);
}

BlockType DesertBiome::getTopBlock() {
    return BlockType::Sand;
}

BlockType DesertBiome::getMiddleBlock() {
    return BlockType::Sand;
}

BlockType DesertBiome::getBottomBlock() {
    return BlockType::Stone;
}