#include "TerrainSampler.h"

#include "../noise/FBMNoise.h"
#include "../noise/RidgeNoise.h"

#include <cmath>

#include "../../core/Setting.h"

TerrainSample TerrainSampler::sample(int worldX, int worldZ) {
  TerrainSample terrain;

  /*
      CONTINENTALNESS

      -1 = ocean
       1 = inland
  */

  terrain.continentalness =
      (FBMNoise::generate(worldX, worldZ, 4, 0.5f, Setting::continentalScale,
                          Setting::seed) +
       1.0f) *
      0.5f;

  /*
      PEAKS

      0 = valley
      1 = mountain
  */

  terrain.peaks = RidgeNoise::generate(
      worldX, worldZ, 5, 0.5f, Setting::peaksScale, Setting::seed + 100);

  /*
      EROSION

      0 = rough
      1 = smooth
  */

  terrain.erosion =
      (FBMNoise::generate(worldX, worldZ, 4, 0.5f, Setting::erosionScale,
                          Setting::seed + 200) +
       1.0f) *
      0.5f;

  /*
      RIVER

      0 = river center
      1 = far from river
  */

  terrain.river = std::abs(FBMNoise::generate(
      worldX, worldZ, 3, 0.5f, Setting::riverScale, Setting::seed + 300));

  return terrain;
} 