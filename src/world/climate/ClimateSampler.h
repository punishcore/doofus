#pragma once

#include "ClimateSample.h"

class ClimateSampler
{
public:

    static ClimateSample sample(
        int worldX,
        int worldZ
    );
};