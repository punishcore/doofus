#include "Chunk.h"

static constexpr float TILE_SIZE = 1.0f / 4.0f;

static int getTopTexture(BlockType type) {
  switch (type) {
  case BlockType::Grass:
    return 0;

  case BlockType::Dirt:
    return 2;

  case BlockType::Stone:
    return 3;

  default:
    return 3;
  }
}

static int getSideTexture(BlockType type) {
  switch (type) {
  case BlockType::Grass:
    return 1;

  case BlockType::Dirt:
    return 2;

  case BlockType::Stone:
    return 3;

  default:
    return 3;
  }
}

static int getBottomTexture(BlockType type) {
  switch (type) {
  case BlockType::Grass:
    return 2;

  case BlockType::Dirt:
    return 2;

  case BlockType::Stone:
    return 3;

  default:
    return 3;
  }
}

static void pushVertex(std::vector<float> &vertices, float x, float y, float z,
                       float u, float v) {
  vertices.push_back(x);
  vertices.push_back(y);
  vertices.push_back(z);

  vertices.push_back(u);
  vertices.push_back(v);
}

Chunk::Chunk(int x, int z) {
  chunkX = x;
  chunkZ = z;
}

bool Chunk::isAir(int x, int y, int z) {
  if (x < 0 || x >= SIZE || y < 0 || y >= HEIGHT || z < 0 || z >= SIZE) {
    return true;
  }

  return blocks[x][y][z] == BlockType::Air;
}

void Chunk::addFace(const float *face, int count, float worldX, float worldY,
                    float worldZ, int tileIndex) {
  constexpr float ATLAS_SIZE = 512.0f;

  constexpr float TILE_SIZE_PX = 16.0f;

  constexpr float PADDING = 1.0f;

  constexpr float CELL_SIZE = TILE_SIZE_PX + (PADDING * 2.0f);

  constexpr int TILES_PER_ROW = 28;

  /*
      TILE POSITION
  */

  int column = tileIndex % TILES_PER_ROW;

  int row = tileIndex / TILES_PER_ROW;

  /*
      PIXEL POSITION
  */

  float pixelX = column * CELL_SIZE + PADDING;

  float pixelY = row * CELL_SIZE + PADDING;

  /*
      NORMALIZED UV
  */

  float u0 = pixelX / ATLAS_SIZE;

  float v0 = pixelY / ATLAS_SIZE;

  float u1 = (pixelX + TILE_SIZE_PX) / ATLAS_SIZE;

  float v1 = (pixelY + TILE_SIZE_PX) / ATLAS_SIZE;

  /*
      STBI FLIP FIX
  */

  v0 = 1.0f - v0;
  v1 = 1.0f - v1;

  /*
      UVS
  */

  float uv[] = {
    u0, v1,
    u1, v1,
    u1, v0,

    u0, v1,
    u1, v0,
    u0, v0
  };

  int uvIndex = 0;

  for (int i = 0; i < count; i += 3) {
    pushVertex(vertices,

               face[i + 0] + worldX, face[i + 1] + worldY, face[i + 2] + worldZ,

               uv[uvIndex], uv[uvIndex + 1]);

    uvIndex += 2;
  }
}

void Chunk::buildMesh() {
  vertices.clear();

  const float topFace[] = {0, 1, 1, 1, 1, 1, 1, 1, 0,

                           0, 1, 1, 1, 1, 0, 0, 1, 0};

  const float bottomFace[] = {0, 0, 0, 1, 0, 0, 1, 0, 1,

                              0, 0, 0, 1, 0, 1, 0, 0, 1};

  const float frontFace[] = {0, 0, 1, 1, 0, 1, 1, 1, 1,

                             0, 0, 1, 1, 1, 1, 0, 1, 1};

  const float backFace[] = {1, 0, 0, 0, 0, 0, 0, 1, 0,

                            1, 0, 0, 0, 1, 0, 1, 1, 0};

  const float leftFace[] = {0, 0, 0, 0, 0, 1, 0, 1, 1,

                            0, 0, 0, 0, 1, 1, 0, 1, 0};

  const float rightFace[] = {1, 0, 1, 1, 0, 0, 1, 1, 0,

                             1, 0, 1, 1, 1, 0, 1, 1, 1};

  for (int x = 0; x < SIZE; x++)
    for (int y = 0; y < HEIGHT; y++)
      for (int z = 0; z < SIZE; z++) {
        BlockType block = blocks[x][y][z];

        if (block == BlockType::Air)
          continue;

        float wx = chunkX * SIZE + x;

        float wy = y;

        float wz = chunkZ * SIZE + z;

        int topTile = getTopTexture(block);

        int sideTile = getSideTexture(block);

        int bottomTile = getBottomTexture(block);

        if (isAir(x, y + 1, z))
          addFace(topFace, 18, wx, wy, wz, topTile);

        if (isAir(x, y - 1, z))
          addFace(bottomFace, 18, wx, wy, wz, bottomTile);

        if (isAir(x, y, z + 1))
          addFace(frontFace, 18, wx, wy, wz, sideTile);

        if (isAir(x, y, z - 1))
          addFace(backFace, 18, wx, wy, wz, sideTile);

        if (isAir(x - 1, y, z))
          addFace(leftFace, 18, wx, wy, wz, sideTile);

        if (isAir(x + 1, y, z))
          addFace(rightFace, 18, wx, wy, wz, sideTile);
      }

  if (!vertices.empty()) {
    mesh = std::make_unique<Mesh>(vertices.data(),
                                  vertices.size() * sizeof(float));
  }
}

void Chunk::draw() {
  if (mesh) {
    mesh->draw();
  }
}