#pragma once

#include "Chunk.h"

#include <memory>
#include <unordered_map>
#include <vector>

class World {
public:

    std::unordered_map<
        long long,
        std::unique_ptr<Chunk>
    > chunks;

    /*
        CHUNK LOAD QUEUE
    */

    std::vector<
        std::pair<int,int>
    > chunkQueue;

    void update(
        float playerX,
        float playerZ
    );

    void draw(
        float playerX,
        float playerZ
    );

    bool isSolid(
        int x,
        int y,
        int z
    );

    int getHeight(
        int x,
        int z
    );

    Chunk* getChunk(
        int chunkX,
        int chunkZ
    );

    void loadChunk(
        int chunkX,
        int chunkZ
    );

    void unloadFarChunks(
        int centerChunkX,
        int centerChunkZ
    );

    long long getChunkKey(
        int x,
        int z
    );

    void setBlock(
        int x,
        int y,
        int z,
        BlockType type
    );
};