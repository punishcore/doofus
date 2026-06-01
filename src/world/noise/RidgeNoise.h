#pragma once

class RidgeNoise {
public:

    static float generate(
        float x,
        float z,
        int octaves,
        float persistence,
        float scale,
        int seed
    );
};