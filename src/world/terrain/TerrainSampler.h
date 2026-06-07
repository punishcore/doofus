#pragma once

#include "TerrainSample.h"

class TerrainSampler
{
public:
    static TerrainSample sample(
        int worldX,
        int worldZ
    );
};