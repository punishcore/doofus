#include "PlainBiome.h"
#include "../../noise/FBMNoise.h"
#include "../../../core/Setting.h"

int PlainBiome::getBaseHeight(int worldX, int worldZ) {
    float n = FBMNoise::generate(
    worldX,
    worldZ,
    5,
    0.5f,
    0.008f,
    Setting::seed
);
    return 40 + (int)(n * 10.0f);
}

BlockType PlainBiome::getTopBlock() {
    return BlockType::Grass;
}

BlockType PlainBiome::getMiddleBlock() {
    return BlockType::Dirt;
}

BlockType PlainBiome::getBottomBlock() {
    return BlockType::Stone;
}