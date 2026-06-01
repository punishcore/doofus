#include "Noise.h"

#include <cmath>

float Noise::lerp(
    float a,
    float b,
    float t
) {
    return a + t * (b - a);
}

float Noise::random(
    int x,
    int z,
    int seed
) {

    int n =
        x + z * 57 + seed;

    n = (n << 13) ^ n;

    return 1.0f -
        (
            (
                n * (
                    n * n * 15731
                    + 789221
                )
                + 1376312589
            )
            & 0x7fffffff
        ) / 1073741824.0f;
}

float Noise::smooth(
    float x,
    float z,
    int seed
) {

    int ix =
        (int)std::floor(x);

    int iz =
        (int)std::floor(z);

    float fx = x - ix;
    float fz = z - iz;

    float v1 =
        random(ix, iz, seed);

    float v2 =
        random(ix + 1, iz, seed);

    float v3 =
        random(ix, iz + 1, seed);

    float v4 =
        random(ix + 1, iz + 1, seed);

    float i1 =
        lerp(v1, v2, fx);

    float i2 =
        lerp(v3, v4, fx);

    return lerp(i1, i2, fz);
}