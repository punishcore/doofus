#include "BiomeManager.h"

#include "plain/PlainBiome.h"
#include "desert/DesertBiome.h"
#include "../../core/Setting.h"
#include "../noise/FBMNoise.h"

// single instances (no heap)
static PlainBiome plain;
static DesertBiome desert;

// optional: fast cache (per chunk column usage)
Biome* BiomeManager::getBiome(int worldX, int worldZ) {

    float biomeNoise =
    FBMNoise::generate(
        worldX,
        worldZ,
        2,
        0.5f,
        Setting::biomeScale,
        Setting::seed
    );

    // normalize
    biomeNoise = (biomeNoise + 1.0f) * 0.5f;

    return (biomeNoise < Setting::plainsChance)
    ? static_cast<Biome*>(&plain)
    : static_cast<Biome*>(&desert);
}