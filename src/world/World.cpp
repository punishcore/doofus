#include "World.h"
#include "../core/Setting.h"
#include "../renderer/Frustum.h"

#include <cmath>
#include <cstring>
#include <iostream>

World::World() { worker = std::make_unique<ChunkWorker>(this); }

World::~World() = default;

long long World::getChunkKey(int x, int z) {
  return ((long long)(unsigned int)x << 32) | (unsigned int)z;
}

// ───────────────────────────────────────
//   Chunk lookup
// ───────────────────────────────────────

Chunk *World::getChunk(int chunkX, int chunkZ) {
  long long key = getChunkKey(chunkX, chunkZ);
  auto it = chunks.find(key);
  return it != chunks.end() ? it->second.get() : nullptr;
}

std::shared_ptr<Chunk> World::getChunkShared(int chunkX, int chunkZ) {
  std::shared_lock lock(chunksMutex);
  long long key = getChunkKey(chunkX, chunkZ);
  auto it = chunks.find(key);
  return it != chunks.end() ? it->second : nullptr;
}

// ───────────────────────────────────────
//   Dirty / remesh
// ───────────────────────────────────────

void World::markChunkDirty(Chunk *chunk) {
  if (!chunk || chunk->dirty)
    return;
  chunk->dirty = true;
  remeshQueue.push(getChunkKey(chunk->chunkX, chunk->chunkZ));
}

// ───────────────────────────────────────
//   Load
// ───────────────────────────────────────

void World::loadChunk(int chunkX, int chunkZ, int playerChunkX,
                      int playerChunkZ) {
  long long key = getChunkKey(chunkX, chunkZ);

  if (chunks.contains(key))
    return;

  auto it = queuedChunks.find(key);
  if (it != queuedChunks.end() && it->second == worker->generation.load())
    return;

  queuedChunks[key] = worker->generation.load();

  int dx = chunkX - playerChunkX;
  int dz = chunkZ - playerChunkZ;
  int priority = dx * dx + dz * dz;

  worker->requestChunk(chunkX, chunkZ, priority, worker->generation.load());
}

// ───────────────────────────────────────
//   Update
// ───────────────────────────────────────

void World::update(float playerX, float playerZ) {
  int playerChunkX = (int)std::floor(playerX / Chunk::SIZE);
  int playerChunkZ = (int)std::floor(playerZ / Chunk::SIZE);

  static int lastChunkX = INT_MAX;
  static int lastChunkZ = INT_MAX;

  if (playerChunkX != lastChunkX || playerChunkZ != lastChunkZ) {
    worker->nextGeneration();
    worker->clearRequests();
    worker->flushFinished();
    queuedChunks.clear();
    remeshQueue = {};

    for (auto &[key, chunk] : chunks) {
      chunk->dirty = false;
      markChunkDirty(chunk.get());
    }

    lastChunkX = playerChunkX;
    lastChunkZ = playerChunkZ;
  }

  // Request terrain
  for (int x = -Setting::renderDistance; x <= Setting::renderDistance; x++) {
    for (int z = -Setting::renderDistance; z <= Setting::renderDistance; z++) {
      if (x * x + z * z > Setting::renderDistance * Setting::renderDistance)
        continue;
      loadChunk(playerChunkX + x, playerChunkZ + z, playerChunkX, playerChunkZ);
    }
  }

  // Accepting terrain from worker
  GeneratedChunk result;
  while (worker->popFinishedChunk(result)) {
    if (result.generation != worker->generation.load())
      continue;

    int cx = result.chunk->chunkX;
    int cz = result.chunk->chunkZ;
    long long key = getChunkKey(cx, cz);

    chunks[key] = std::move(result.chunk);
    queuedChunks.erase(key);

    for (auto [ncx, ncz] : std::initializer_list<std::pair<int, int>>{
             {cx, cz},
             {cx - 1, cz},
             {cx + 1, cz},
             {cx, cz - 1},
             {cx, cz + 1},
         }) {
      Chunk *n = getChunk(ncx, ncz);
      if (!n)
        continue;
      n->dirty = false;
      markChunkDirty(n);
    }
  }

  // Send mesh request to worker (using priority)
  const int MAX_MESH_DISPATCH = 4;
  int dispatched = 0;

  // Di dalam World::update (Bagian dispatch mesh)
  // Di dalam World::update (Bagian dispatch mesh)
  while (!remeshQueue.empty() && dispatched < MAX_MESH_DISPATCH) {
    long long key = remeshQueue.front();
    remeshQueue.pop();

    auto it = chunks.find(key);
    if (it == chunks.end())
      continue;
    auto chunk = it->second; // shared_ptr jika sudah diubah
    if (!chunk->dirty)
      continue;

    // KUNCI PERBAIKAN: Hitung dx dan dz di sini terlebih dahulu!
    int dx = std::abs(chunk->chunkX - playerChunkX);
    int dz = std::abs(chunk->chunkZ - playerChunkZ);

    if (dx > Setting::renderDistance || dz > Setting::renderDistance) {
      chunk->dirty = false;
      continue;
    }

    auto nNX = getChunkShared(chunk->chunkX - 1, chunk->chunkZ);
    auto nPX = getChunkShared(chunk->chunkX + 1, chunk->chunkZ);
    auto nNZ = getChunkShared(chunk->chunkX, chunk->chunkZ - 1);
    auto nPZ = getChunkShared(chunk->chunkX, chunk->chunkZ + 1);

    if (!nNX || !nPX || !nNZ || !nPZ) {
      continue;
    }

    MeshRequest meshReq;
    meshReq.chunk = chunk.get();
    meshReq.priority =
        dx * dx + dz * dz; // Sekarang dx dan dz sudah aman digunakan!
    meshReq.generation = worker->generation.load();

    meshReq.mainChunk = chunk;
    meshReq.nNX = nNX;
    meshReq.nPX = nPX;
    meshReq.nNZ = nNZ;
    meshReq.nPZ = nPZ;

    worker->enqueueMeshRequest(std::move(meshReq));
    dispatched++;
  }

  // Accept result mesh from worker, upload on main thread
  MeshResult meshResult;
  while (worker->popFinishedMesh(meshResult)) {
    if (meshResult.generation != worker->generation.load())
      continue;

    Chunk *chunk = meshResult.chunk;
    chunk->pendingVertices = std::move(meshResult.vertices);
    chunk->empty.store(chunk->pendingVertices.empty());
    chunk->uploadMesh();
    chunk->dirty = false;
  }

  unloadFarChunks(playerChunkX, playerChunkZ);
}

// ───────────────────────────────────────
//   Draw
// ───────────────────────────────────────

void World::draw(float playerX, float playerZ, const Frustum &frustum) {
  int playerChunkX = (int)std::floor(playerX / Chunk::SIZE);
  int playerChunkZ = (int)std::floor(playerZ / Chunk::SIZE);

  for (auto &[key, chunk] : chunks) {
    int dx = std::abs(chunk->chunkX - playerChunkX);
    int dz = std::abs(chunk->chunkZ - playerChunkZ);

    if (dx > Setting::renderDistance || dz > Setting::renderDistance)
      continue;
    if (chunk->empty)
      continue;
    if (!chunk->mesh) {
      continue;
    }
    if (!frustum.isBoxVisible(chunk->getMinBounds(), chunk->getMaxBounds()))
      continue;

    chunk->draw();
  }
}

// ───────────────────────────────────────
//   Block ops
// ───────────────────────────────────────

bool World::isSolid(int x, int y, int z) {
  Chunk *chunk = getChunk((int)std::floor((float)x / Chunk::SIZE),
                          (int)std::floor((float)z / Chunk::SIZE));
  if (!chunk)
    return false;

  int lx = x % Chunk::SIZE;
  if (lx < 0)
    lx += Chunk::SIZE;
  int lz = z % Chunk::SIZE;
  if (lz < 0)
    lz += Chunk::SIZE;

  if (y < 0 || y >= Chunk::HEIGHT)
    return false;
  return chunk->blocks[lx][y][lz] != BlockType::Air;
}

int World::getHeight(int x, int z) {
  for (int y = Chunk::HEIGHT - 1; y >= 0; y--)
    if (isSolid(x, y, z))
      return y;
  return 0;
}

void World::setBlock(int x, int y, int z, BlockType type) {
  int chunkX = (int)std::floor((float)x / Chunk::SIZE);
  int chunkZ = (int)std::floor((float)z / Chunk::SIZE);
  Chunk *chunk = getChunk(chunkX, chunkZ);
  if (!chunk)
    return;

  int lx = x % Chunk::SIZE;
  if (lx < 0)
    lx += Chunk::SIZE;
  int lz = z % Chunk::SIZE;
  if (lz < 0)
    lz += Chunk::SIZE;
  if (y < 0 || y >= Chunk::HEIGHT)
    return;

  chunk->blocks[lx][y][lz] = type;
  markChunkDirty(chunk);

  if (lx == 0)
    if (auto *n = getChunk(chunkX - 1, chunkZ))
      markChunkDirty(n);
  if (lx == Chunk::SIZE - 1)
    if (auto *n = getChunk(chunkX + 1, chunkZ))
      markChunkDirty(n);
  if (lz == 0)
    if (auto *n = getChunk(chunkX, chunkZ - 1))
      markChunkDirty(n);
  if (lz == Chunk::SIZE - 1)
    if (auto *n = getChunk(chunkX, chunkZ + 1))
      markChunkDirty(n);
}

// ───────────────────────────────────────
//   Unload
// ───────────────────────────────────────

void World::unloadFarChunks(int centerChunkX, int centerChunkZ) {
  const int UNLOAD_DISTANCE = Setting::renderDistance + 2;

  for (auto it = chunks.begin(); it != chunks.end();) {
    Chunk *chunk = it->second.get();
    int dx = std::abs(chunk->chunkX - centerChunkX);
    int dz = std::abs(chunk->chunkZ - centerChunkZ);

    if (dx > UNLOAD_DISTANCE || dz > UNLOAD_DISTANCE)
      it = chunks.erase(it);
    else
      ++it;
  }
}