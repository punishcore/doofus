#include "PlainBiome.h"

BlockType PlainBiome::getTopBlock()
{
    return BlockType::Grass;
}

BlockType PlainBiome::getMiddleBlock()
{
    return BlockType::Dirt;
}

BlockType PlainBiome::getBottomBlock()
{
    return BlockType::Stone;
}

