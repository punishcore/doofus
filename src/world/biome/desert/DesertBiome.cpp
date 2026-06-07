#include "DesertBiome.h"

BlockType DesertBiome::getTopBlock()
{
    return BlockType::Sand;
}

BlockType DesertBiome::getMiddleBlock()
{
    return BlockType::Sand;
}

BlockType DesertBiome::getBottomBlock()
{
    return BlockType::Stone;
}
