#include "ChunkWorker.h"
#include "TerrainGenerator.h"
#include "World.h"
#include "mesher/GreedyMesher.h"
#include <algorithm>
#include <cstring>

ChunkWorker::ChunkWorker(World* worldPtr) {
    world = worldPtr;
    const unsigned int N = std::max(1u, std::thread::hardware_concurrency());
    for (unsigned int i = 0; i < N; i++)
        workers.emplace_back(&ChunkWorker::run, this);
}

ChunkWorker::~ChunkWorker() {
    running.store(false);
    cv.notify_all();
    for (auto& w : workers)
        if (w.joinable()) w.join();
}

void ChunkWorker::requestChunk(int x, int z, int priority, uint32_t gen) {
    { std::lock_guard lock(mutex); requests.push({x, z, priority, gen}); }
    cv.notify_one();
}

void ChunkWorker::enqueueMeshRequest(MeshRequest req) {
    { std::lock_guard lock(mutex); meshRequests.push(std::move(req)); }
    cv.notify_one();
}

bool ChunkWorker::popFinishedChunk(GeneratedChunk& result) {
    std::lock_guard lock(mutex);
    if (finished.empty()) return false;
    result = std::move(finished.front());
    finished.pop();
    return true;
}

bool ChunkWorker::popFinishedMesh(MeshResult& result) {
    std::lock_guard lock(mutex);
    if (finishedMeshes.empty()) return false;
    result = std::move(finishedMeshes.front());
    finishedMeshes.pop();
    return true;
}

void ChunkWorker::clearRequests() {
    std::lock_guard lock(mutex);
    requests = {};
    meshRequests = {};
}

void ChunkWorker::flushFinished() {
    std::lock_guard lock(mutex);
    uint32_t gen = generation.load();

    std::queue<GeneratedChunk> newFinished;
    while (!finished.empty()) {
        if (finished.front().generation == gen)
            newFinished.push(std::move(finished.front()));
        finished.pop();
    }
    finished = std::move(newFinished);

    std::queue<MeshResult> newMeshes;
    while (!finishedMeshes.empty()) {
        if (finishedMeshes.front().generation == gen)
            newMeshes.push(std::move(finishedMeshes.front()));
        finishedMeshes.pop();
    }
    finishedMeshes = std::move(newMeshes);
}

void ChunkWorker::run() {
    while (running.load()) {
        ChunkRequest req;
        MeshRequest  meshReq;
        bool hasTerrain = false;
        bool hasMesh    = false;

        {
            std::unique_lock lock(mutex);
            cv.wait(lock, [&] {
                return !requests.empty() || !meshRequests.empty() || !running.load();
            });
            if (!running.load()) break;

            if (!meshRequests.empty()) {
                meshReq = std::move(const_cast<MeshRequest&>(meshRequests.top()));
                meshRequests.pop();
                hasMesh = true;
            } else if (!requests.empty()) {
                req = requests.top();
                requests.pop();
                hasTerrain = true;
            }
        }

        //  Mesh 
        if (hasMesh) {
            if (meshReq.generation != generation.load()) continue;

            Chunk tempMain(meshReq.chunkX, meshReq.chunkZ, nullptr);
            Chunk tempNX(0, 0, nullptr), tempPX(0, 0, nullptr);
            Chunk tempNZ(0, 0, nullptr), tempPZ(0, 0, nullptr);

            memcpy(tempMain.blocks, meshReq.blocksMain, sizeof(tempMain.blocks));
            memcpy(tempNX.blocks,   meshReq.blocksNX,   sizeof(tempNX.blocks));
            memcpy(tempPX.blocks,   meshReq.blocksPX,   sizeof(tempPX.blocks));
            memcpy(tempNZ.blocks,   meshReq.blocksNZ,   sizeof(tempNZ.blocks));
            memcpy(tempPZ.blocks,   meshReq.blocksPZ,   sizeof(tempPZ.blocks));

            GreedyMesher::build(tempMain, &tempNX, &tempPX, &tempNZ, &tempPZ);

            if (meshReq.generation != generation.load()) continue;

            MeshResult result;
            result.chunk      = meshReq.chunk;
            result.vertices   = std::move(tempMain.vertices);
            result.generation = meshReq.generation;

            std::lock_guard lock(mutex);
            finishedMeshes.push(std::move(result));
        }

        //  Terrain 
        if (hasTerrain) {
            if (req.generation != generation.load()) continue;

            auto chunk = std::make_unique<Chunk>(req.x, req.z, world);
            TerrainGenerator::generate(*chunk);

            if (req.generation != generation.load()) continue;

            GeneratedChunk result;
            result.chunk      = std::move(chunk);
            result.generation = req.generation;

            std::lock_guard lock(mutex);
            finished.push(std::move(result));
        }
    }
}