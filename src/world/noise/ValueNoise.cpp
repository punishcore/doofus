#include "ValueNoise.h"
#include "Noise.h"

float ValueNoise::generate(
    float x,
    float z,
    int seed
) {
    return Noise::smooth(
        x,
        z,
        seed
    );
}