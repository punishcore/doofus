#pragma once

#include "Biome.h"
#include <array>

class BiomeManager {
public:
    static Biome* getBiome(int worldX, int worldZ);
};