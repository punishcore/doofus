#include "TerrainGenerator.h"
#include "Noise.h"

#include <cmath>

static float clamp(float v, float min, float max) {
  if (v < min)
    return min;
  if (v > max)
    return max;

  return v;
}

void TerrainGenerator::generate(Chunk &chunk) {
  for (int x = 0; x < Chunk::SIZE; x++)
    for (int z = 0; z < Chunk::SIZE; z++) {
      int worldX = chunk.chunkX * Chunk::SIZE + x;

      int worldZ = chunk.chunkZ * Chunk::SIZE + z;

      /*
          CONTINENTS
          BIG LAND SHAPE
      */

      float continent = Noise::fbm(worldX, worldZ, 4, 0.5f, 0.0015f);

      /*
          MOUNTAINS
      */

      float mountain = Noise::fbm(worldX, worldZ, 6, 0.5f, 0.008f);

      mountain = std::abs(mountain);

      mountain = std::pow(mountain, 3.0f);

      /*
          HILLS
      */

      float hills = Noise::fbm(worldX, worldZ, 4, 0.5f, 0.02f);

      /*
          DETAIL
      */

      float detail = Noise::fbm(worldX, worldZ, 2, 0.5f, 0.08f);

      /*
          FINAL TERRAIN
      */

      float terrainHeight =
          continent * 35.0f + mountain * 90.0f + hills * 10.0f + detail * 2.0f;

      /*
          FLATTEN LOW AREAS
      */

      if (terrainHeight < 15.0f) {
        terrainHeight *= 0.6f;
      }

      int height = 20 + (int)terrainHeight;

      height = (int)clamp(height, 1, Chunk::HEIGHT - 1);

      /*
          BLOCK LAYERS
      */

      for (int y = 0; y < Chunk::HEIGHT; y++) {
        if (y > height) {
          chunk.blocks[x][y][z] = BlockType::Air;
        } else if (y == height) {
          chunk.blocks[x][y][z] = BlockType::Grass;
        } else if (y > height - 4) {
          chunk.blocks[x][y][z] = BlockType::Dirt;
        } else {
          chunk.blocks[x][y][z] = BlockType::Stone;
        }
      }
    }

  chunk.dirty = true;
}