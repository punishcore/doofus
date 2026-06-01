#pragma once

#include "BlockType.h"

struct BlockUV {
  float u1;
  float v1;

  float u2;
  float v2;
};

class BlockData {
public:
  static BlockUV get(BlockType type) {
    float tile = 1.0f / 4.0f;

    switch (type) {
    case BlockType::Grass:
      return {0.0f, 0.0f, tile, tile};

    case BlockType::Dirt:
      return {tile, 0.0f, tile * 2.0f, tile};

    case BlockType::Stone:
      return {tile * 2.0f, 0.0f, tile * 3.0f, tile};

    case BlockType::Sand:
            return {
                tile * 3.0f,
                0.0f,

                tile * 4.0f,
                tile
            };

    default:
      return {0, 0, 0, 0};
    }
  }
};