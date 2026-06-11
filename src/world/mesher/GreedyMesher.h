#pragma once
#include <vector>

class Chunk;

class GreedyMesher {
public:
    static void build(const Chunk &chunk, Chunk *neighborNX, Chunk *neighborPX,
                      Chunk *neighborNZ, Chunk *neighborPZ, std::vector<float> &outVertices);
};