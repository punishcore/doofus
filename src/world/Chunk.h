#pragma once

#include "../renderer/opengl/Mesh.h"
#include "block/BlockType.h"

#include <memory>
#include <vector>

class World;
class GreedyMesher;

class Chunk {
public:

    static constexpr int SIZE = 16;
    static constexpr int HEIGHT = 128;

    int heightMap[SIZE][SIZE];

    int chunkX;
    int chunkZ;

    bool dirty = true;
    bool empty = true;

    World* world;

    Chunk* leftChunk = nullptr;
    Chunk* rightChunk = nullptr;
    Chunk* frontChunk = nullptr;
    Chunk* backChunk = nullptr;

    BlockType blocks[SIZE][HEIGHT][SIZE];

    std::unique_ptr<Mesh> mesh;

    std::vector<float> vertices;

    Chunk(
        int x,
        int z,
        World* world
    );

    void buildMesh();

    void draw();

    inline BlockType getBlock(int x, int y, int z) const
{
    if (x < 0 || x >= SIZE ||
        y < 0 || y >= HEIGHT ||
        z < 0 || z >= SIZE)
        return BlockType::Air;

    return blocks[x][y][z];
}

    friend class GreedyMesher;

private:


    void addFace(
        const float* face,
        int count,
        float wx,
        float wy,
        float wz,
        int tileIndex
    );
};