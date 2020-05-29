//
// Created by erikdesk on 5/29/20.
//

#include "TerrainGenerator.h"

TerrainGenerator::TerrainGenerator(BlockManager& blockManager, GameDataRef data)
:blockManager(blockManager)
{
    this->data = data;

    if(chunkMap.find(std::tuple<int,int>(0,0))==chunkMap.end()){
        generateChunk(0,0);
        generateChunk(0,1);
        generateChunk(1,0);
    }

}

TerrainGenerator::~TerrainGenerator() {

}

void TerrainGenerator::generateChunk(int xLoc, int zLoc) {
    std::tuple<int,int> loc(xLoc,zLoc);
    chunkMap.insert(std::pair<std::tuple<int,int>,int>(loc,chunkCounter));
    chunkCounter++;

    for (int x = 0; x < chunkWidth; ++x) {
        for (int y = 0; y < chunkHeight; ++y) {
            for (int z = 0; z < chunkLength; ++z) {
                blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+x*2,y*2,zLoc*chunkLength*2+z*2),"cobble",chunkCounter);
            }
        }
    }


}

void TerrainGenerator::Update() {

}
