#pragma once

class Noise {
public:

    static float random(
        int x,
        int z,
        int seed
    );

    static float lerp(
        float a,
        float b,
        float t
    );

    static float smooth(
        float x,
        float z,
        int seed
    );
};