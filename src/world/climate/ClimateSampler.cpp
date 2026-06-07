#include "ClimateSampler.h"

#include "../noise/FBMNoise.h"

#include "../../core/Setting.h"

ClimateSample ClimateSampler::sample(int worldX, int worldZ) {
  ClimateSample climate;

  climate.temperature =
      (FBMNoise::generate(worldX, worldZ, 3, 0.5f, Setting::temperatureScale,
                          Setting::seed + 400) +
       1.0f) *
      0.5f;

  climate.humidity =
      (FBMNoise::generate(worldX, worldZ, 3, 0.5f, Setting::humidityScale,
                          Setting::seed + 500) +
       1.0f) *
      0.5f;

  return climate;
}