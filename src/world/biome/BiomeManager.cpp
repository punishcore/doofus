#include "BiomeManager.h"

#include "../../core/Setting.h"
#include "desert/DesertBiome.h"
#include "mountain/MountainBiome.h"
#include "plain/PlainBiome.h"

static PlainBiome plain;
static DesertBiome desert;
static MountainBiome mountain;

Biome *BiomeManager::getBiome(const TerrainSample &terrain,
                              const ClimateSample &climate) {
  /*
      MOUNTAIN
  */

  if (terrain.peaks > Setting::mountainThreshold) {
    return &mountain;
  }

  /*
      DESERT
  */

  if (climate.temperature > Setting::desertTemperature &&
      climate.humidity < Setting::desertHumidity) {
    return &desert;
  }
  // if (terrain.continentalness < 0.25f)
  // {
  //     return &river;
  // }

  /*
      PLAINS
  */

  return &plain;
}