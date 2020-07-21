//
// Created by erikdesk on 5/29/20.
//

#ifndef GLENGINE_TERRAINGENERATOR_H
#define GLENGINE_TERRAINGENERATOR_H

#include <future>
#include "ChunkManager.h"
#include "../Managers.h"

class TerrainGenerator {
public:
    TerrainGenerator(GameDataRef data);
    ~TerrainGenerator();

    void Update();
    std::shared_ptr<ChunkManager> GetChunk(int x, int y , int z);
    int getCount();
private:
    GameDataRef data;

    float heightMulti = 16;
    int chunkWidth = CHUNKSIZE;
    int chunkLength = CHUNKSIZE;
    float hardness = 0.8;
    void generateChunk(int xLoc, int zLoc, std::shared_ptr<ChunkManager> manager);

    std::tuple<int,int,int> CurrentChunk;

    std::map<std::tuple<int,int,int>,std::shared_ptr<ChunkManager>> ChunkMap;
    std::map<std::tuple<int,int,int>,std::shared_ptr<ChunkManager>> PendingChunks;
    std::map<std::tuple<int,int,int>,std::shared_ptr<ChunkManager>> RenderList;
    void insertChunkManager(std::shared_ptr<ChunkManager> man, int x, int y, int z);

    std::vector<std::future<void>> futures;
};

#endif //GLENGINE_TERRAINGENERATOR_H