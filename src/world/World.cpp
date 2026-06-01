#include "World.h"

#include "TerrainGenerator.h"
#include "../core/Setting.h"

#include <cmath>

long long World::getChunkKey(
    int x,
    int z
) {

    return
        ((long long)x << 32)
        ^
        (unsigned int)z;
}

Chunk* World::getChunk(
    int chunkX,
    int chunkZ
) {

    long long key =
        getChunkKey(
            chunkX,
            chunkZ
        );

    auto it =
        chunks.find(key);

    if (
        it ==
        chunks.end()
    ) {
        return nullptr;
    }

    return it->second.get();
}

void World::loadChunk(
    int chunkX,
    int chunkZ
) {

    long long key =
        getChunkKey(
            chunkX,
            chunkZ
        );

    /*
        ALREADY LOADED
    */

    if (
        chunks.find(key)
        !=
        chunks.end()
    ) {
        return;
    }

    /*
        PREVENT DUPLICATE
    */

    for (auto& c : chunkQueue) {

        if (
            c.first == chunkX
            &&
            c.second == chunkZ
        ) {
            return;
        }
    }

    /*
        PUSH TO QUEUE
    */

    chunkQueue.push_back({
        chunkX,
        chunkZ
    });
}

void World::update(
    float playerX,
    float playerZ
) {

    int playerChunkX =
        (int)std::floor(
            playerX / Chunk::SIZE
        );

    int playerChunkZ =
        (int)std::floor(
            playerZ / Chunk::SIZE
        );

    /*
        REQUEST CHUNKS
    */

    for (
        int x = -Setting::renderDistance;
        x <= Setting::renderDistance;
        x++
    ) {

        for (
            int z = -Setting::renderDistance;
            z <= Setting::renderDistance;
            z++
        ) {

            loadChunk(
                playerChunkX + x,
                playerChunkZ + z
            );
        }
    }

    /*
        LOAD FEW CHUNKS PER FRAME
    */

    int chunksPerFrame = 2;

    while (
        chunksPerFrame > 0
        &&
        !chunkQueue.empty()
    ) {

        auto [cx, cz] =
            chunkQueue.back();

        chunkQueue.pop_back();

        long long key =
            getChunkKey(cx, cz);

        auto chunk =
            std::make_unique<Chunk>(
                cx,
                cz,
                this
            );

        TerrainGenerator::generate(
            *chunk
        );

        chunk->buildMesh();

        chunks[key] =
            std::move(chunk);

        chunksPerFrame--;
    }

    unloadFarChunks(
        playerChunkX,
        playerChunkZ
    );
}

void World::draw(
    float playerX,
    float playerZ
) {

    int playerChunkX =
        (int)std::floor(
            playerX / Chunk::SIZE
        );

    int playerChunkZ =
        (int)std::floor(
            playerZ / Chunk::SIZE
        );

    for (auto& [key, chunk] : chunks) {

        int dx =
            std::abs(
                chunk->chunkX
                -
                playerChunkX
            );

        int dz =
            std::abs(
                chunk->chunkZ
                -
                playerChunkZ
            );

        if (
            dx > Setting::renderDistance
            ||
            dz > Setting::renderDistance
        ) {
            continue;
        }

        if (chunk->dirty) {

            if (!chunk->empty) {

              chunk->buildMesh();
            }

            chunk->dirty = false;
        }

        if (chunk->empty)
          continue;

        chunk->draw();
    }
}

bool World::isSolid(int x, int y, int z) {

    int chunkX = std::floor((float)x / Chunk::SIZE);
    int chunkZ = std::floor((float)z / Chunk::SIZE);

    Chunk* chunk = getChunk(chunkX, chunkZ);
    if (!chunk) return false;

    int localX = x % Chunk::SIZE;
    int localZ = z % Chunk::SIZE;

    if (localX < 0) localX += Chunk::SIZE;
    if (localZ < 0) localZ += Chunk::SIZE;

    if (y < 0 || y >= Chunk::HEIGHT) return false;

    return chunk->blocks[localX][y][localZ] != BlockType::Air;
}

int World::getHeight(int x, int z) {

    for (int y = Chunk::HEIGHT - 1; y >= 0; y--) {
        if (isSolid(x, y, z)) {
            return y;
        }
    }

    return 0;
}

void World::setBlock(int x, int y, int z, BlockType type) {

    int chunkX = std::floor((float)x / Chunk::SIZE);
    int chunkZ = std::floor((float)z / Chunk::SIZE);

    Chunk* chunk = getChunk(chunkX, chunkZ);
    if (!chunk) return;

    int localX = x % Chunk::SIZE;
    int localZ = z % Chunk::SIZE;

    if (localX < 0) localX += Chunk::SIZE;
    if (localZ < 0) localZ += Chunk::SIZE;

    if (y < 0 || y >= Chunk::HEIGHT) return;

    chunk->blocks[localX][y][localZ] = type;
    chunk->dirty = true;
}

void World::unloadFarChunks(int centerChunkX, int centerChunkZ) {

    for (auto it = chunks.begin(); it != chunks.end(); ) {

        Chunk* c = it->second.get();

        int dx = std::abs(c->chunkX - centerChunkX);
        int dz = std::abs(c->chunkZ - centerChunkZ);

        if (dx > Setting::renderDistance ||
            dz > Setting::renderDistance) {

            it = chunks.erase(it);
        } else {
            ++it;
        }
    }
}