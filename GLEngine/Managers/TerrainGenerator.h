//
// Created by erikdesk on 5/29/20.
//

#ifndef GLENGINE_TERRAINGENERATOR_H
#define GLENGINE_TERRAINGENERATOR_H

#include "BlockManager.h"
#include "../Managers.h"


class TerrainGenerator {
public:
    TerrainGenerator(BlockManager& blockManager, GameDataRef data);
    ~TerrainGenerator();

    void Update();

private:
    GameDataRef data;
    BlockManager& blockManager;
    float heightMulti = 64;
    int chunkWidth = 16;
    int chunkLength = 16;
    float hardness = 0.1;
    uint64_t chunkCounter = 0;
    std::map<std::tuple<int,int>, uint64_t> chunkMap;
    void generateChunk(int xLoc, int zLoc);
};

#endif //GLENGINE_TERRAINGENERATOR_H