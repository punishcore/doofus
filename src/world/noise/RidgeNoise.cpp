#include "RidgeNoise.h"
#include "FBMNoise.h"

#include <cmath>

float RidgeNoise::generate(
    float x,
    float z,
    int octaves,
    float persistence,
    float scale,
    int seed
) {

    float n =
        FBMNoise::generate(
            x,
            z,
            octaves,
            persistence,
            scale,
            seed
        );

    n =
        1.0f - std::abs(n);

    return n * n;
}