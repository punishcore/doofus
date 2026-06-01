#include "FBMNoise.h"
#include "Noise.h"

float FBMNoise::generate(
    float x,
    float z,
    int octaves,
    float persistence,
    float scale,
    int seed
) {

    float total = 0.0f;

    float frequency = scale;

    float amplitude = 1.0f;

    float maxValue = 0.0f;

    for (int i = 0; i < octaves; i++) {

        total +=
            Noise::smooth(
                x * frequency,
                z * frequency,
                seed + i * 1000
            ) * amplitude;

        maxValue += amplitude;

        amplitude *= persistence;

        frequency *= 2.0f;
    }

    return total / maxValue;
}