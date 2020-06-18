//
// Created by erikdesk on 5/29/20.
//

#ifndef GLENGINE_TERRAINGENERATOR_H
#define GLENGINE_TERRAINGENERATOR_H

#include "BlockManager.h"
#include "../Managers.h"


class TerrainGenerator {
public:
    TerrainGenerator(GameDataRef data);
    ~TerrainGenerator();

    void Update();

private:
    GameDataRef data;

    std::vector<std::shared_ptr<BlockManager>> blockManagers;

    float heightMulti = 32;
    int chunkWidth = 32;
    int chunkLength = 32;
    float hardness = 0.8;
    uint64_t chunkCounter = 0;
    std::map<std::tuple<int,int>, uint64_t> chunkMap;
    void generateChunk(int xLoc, int zLoc, int man);
};

#endif //GLENGINE_TERRAINGENERATOR_H