#include "World.h"
#include "TerrainGenerator.h"

#include <cmath>
#include <vector>

long long World::getChunkKey(int x, int z) {
  return ((long long)x << 32) ^ (unsigned int)z;
}

Chunk *World::getChunk(int chunkX, int chunkZ) {
  long long key = getChunkKey(chunkX, chunkZ);

  auto it = chunks.find(key);

  if (it == chunks.end())
    return nullptr;

  return it->second.get();
}

void World::loadChunk(int chunkX, int chunkZ) {
  long long key = getChunkKey(chunkX, chunkZ);

  if (chunks.find(key) != chunks.end())
    return;

  auto chunk = std::make_unique<Chunk>(chunkX, chunkZ);

  TerrainGenerator::generate(*chunk);

  chunk->buildMesh();

  chunks[key] = std::move(chunk);
}

void World::update(float playerX, float playerZ) {
  int playerChunkX = (int)std::floor(playerX / Chunk::SIZE);

  int playerChunkZ = (int)std::floor(playerZ / Chunk::SIZE);

  for (int x = -renderDistance; x <= renderDistance; x++) {
    for (int z = -renderDistance; z <= renderDistance; z++) {
      loadChunk(playerChunkX + x, playerChunkZ + z);
    }
  }

  unloadFarChunks(playerChunkX, playerChunkZ);
}

void World::unloadFarChunks(int centerChunkX, int centerChunkZ) {
  std::vector<long long> removeList;

  for (auto &[key, chunk] : chunks) {
    int dx = std::abs(chunk->chunkX - centerChunkX);

    int dz = std::abs(chunk->chunkZ - centerChunkZ);

    if (dx > renderDistance || dz > renderDistance) {
      removeList.push_back(key);
    }
  }

  while (chunks.size() > 32 && !removeList.empty()) {
    chunks.erase(removeList.back());

    removeList.pop_back();
  }
}

void World::draw(float playerX, float playerZ) {
  int playerChunkX = (int)std::floor(playerX / Chunk::SIZE);

  int playerChunkZ = (int)std::floor(playerZ / Chunk::SIZE);

  for (auto &[key, chunk] : chunks) {
    int dx = std::abs(chunk->chunkX - playerChunkX);

    int dz = std::abs(chunk->chunkZ - playerChunkZ);

    if (dx > renderDistance || dz > renderDistance) {
      continue;
    }

    if (chunk->dirty) {
      chunk->buildMesh();

      chunk->dirty = false;
    }

    chunk->draw();
  }
}

bool World::isSolid(int x, int y, int z) {
  if (y < 0 || y >= Chunk::HEIGHT)
    return false;

  int chunkX = (int)std::floor((float)x / Chunk::SIZE);

  int chunkZ = (int)std::floor((float)z / Chunk::SIZE);

  Chunk *chunk = getChunk(chunkX, chunkZ);

  if (!chunk)
    return false;

  int localX = x - chunkX * Chunk::SIZE;
  int localZ = z - chunkZ * Chunk::SIZE;

  if (localX < 0)
    localX += Chunk::SIZE;

  if (localZ < 0)
    localZ += Chunk::SIZE;

  return chunk->blocks[localX][y][localZ] != BlockType::Air;
}

int World::getHeight(int x, int z) {
  int chunkX = (int)std::floor((float)x / Chunk::SIZE);

  int chunkZ = (int)std::floor((float)z / Chunk::SIZE);

  Chunk *chunk = getChunk(chunkX, chunkZ);

  if (!chunk)
    return 20;

  int localX = x - chunkX * Chunk::SIZE;
  int localZ = z - chunkZ * Chunk::SIZE;

  if (localX < 0)
    localX += Chunk::SIZE;

  if (localZ < 0)
    localZ += Chunk::SIZE;

  for (int y = Chunk::HEIGHT - 1; y >= 0; y--) {
    if (chunk->blocks[localX][y][localZ] != BlockType::Air) {
      return y + 2;
    }
  }

  return 20;
}

void World::setBlock(int x, int y, int z, BlockType type) {
  int chunkX = (int)std::floor((float)x / Chunk::SIZE);

  int chunkZ = (int)std::floor((float)z / Chunk::SIZE);

  Chunk *chunk = getChunk(chunkX, chunkZ);

  if (!chunk)
    return;

  int localX = x - chunkX * Chunk::SIZE;
  int localZ = z - chunkZ * Chunk::SIZE;

  if (localX < 0)
    localX += Chunk::SIZE;

  if (localZ < 0)
    localZ += Chunk::SIZE;

  if (y < 0 || y >= Chunk::HEIGHT)
    return;

  chunk->blocks[localX][y][localZ] = type;

  chunk->dirty = true;
}
