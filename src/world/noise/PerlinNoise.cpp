#include "PerlinNoise.h"
#include "Noise.h"

#include <cmath>

static float fade(float t) {

    return
        t * t * t
        *
        (
            t * (
                t * 6.0f - 15.0f
            )
            + 10.0f
        );
}

static float gradient(
    int hash,
    float x,
    float z
) {

    switch (hash & 3) {

        case 0:
            return  x + z;

        case 1:
            return -x + z;

        case 2:
            return  x - z;

        default:
            return -x - z;
    }
}

float PerlinNoise::generate(
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

    float u = fade(fx);
    float v = fade(fz);

    int h1 =
        (int)(
            Noise::random(
                ix,
                iz,
                seed
            ) * 255
        );

    int h2 =
        (int)(
            Noise::random(
                ix + 1,
                iz,
                seed
            ) * 255
        );

    int h3 =
        (int)(
            Noise::random(
                ix,
                iz + 1,
                seed
            ) * 255
        );

    int h4 =
        (int)(
            Noise::random(
                ix + 1,
                iz + 1,
                seed
            ) * 255
        );

    float g1 =
        gradient(
            h1,
            fx,
            fz
        );

    float g2 =
        gradient(
            h2,
            fx - 1.0f,
            fz
        );

    float g3 =
        gradient(
            h3,
            fx,
            fz - 1.0f
        );

    float g4 =
        gradient(
            h4,
            fx - 1.0f,
            fz - 1.0f
        );

    float lerp1 =
        Noise::lerp(
            g1,
            g2,
            u
        );

    float lerp2 =
        Noise::lerp(
            g3,
            g4,
            u
        );

    return Noise::lerp(
        lerp1,
        lerp2,
        v
    );
}