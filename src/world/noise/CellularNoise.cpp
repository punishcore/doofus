#include "CellularNoise.h"
#include "Noise.h"

#include <cmath>

float CellularNoise::generate(
    float x,
    float z,
    int seed
) {

    int cellX =
        (int)std::floor(x);

    int cellZ =
        (int)std::floor(z);

    float minDist =
        999999.0f;

    for (
        int offsetX = -1;
        offsetX <= 1;
        offsetX++
    ) {

        for (
            int offsetZ = -1;
            offsetZ <= 1;
            offsetZ++
        ) {

            int pointX =
                cellX + offsetX;

            int pointZ =
                cellZ + offsetZ;

            float randomX =
                Noise::random(
                    pointX,
                    pointZ,
                    seed
                );

            float randomZ =
                Noise::random(
                    pointX,
                    pointZ,
                    seed + 999
                );

            float featureX =
                pointX + randomX;

            float featureZ =
                pointZ + randomZ;

            float dx =
                featureX - x;

            float dz =
                featureZ - z;

            float dist =
                std::sqrt(
                    dx * dx
                    +
                    dz * dz
                );

            if (dist < minDist) {
                minDist = dist;
            }
        }
    }

    return minDist;
}