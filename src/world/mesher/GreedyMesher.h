class Chunk;

class GreedyMesher {
public:
  static void build(Chunk &chunk, Chunk *neighborNX, Chunk *neighborPX,
                    Chunk *neighborNZ, Chunk *neighborPZ);
};
