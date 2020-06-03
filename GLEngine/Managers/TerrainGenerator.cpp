//
// Created by erikdesk on 5/29/20.
//

#include "TerrainGenerator.h"
#include "PerlinNoise.h"

TerrainGenerator::TerrainGenerator(BlockManager& blockManager, GameDataRef data)
:blockManager(blockManager)
{
    this->data = data;

    if(chunkMap.find(std::tuple<int,int>(0,0))==chunkMap.end()){
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                generateChunk(i,j);
            }
        }

    }

}

TerrainGenerator::~TerrainGenerator() {

}

void TerrainGenerator::generateChunk(int xLoc, int zLoc) {
    std::tuple<int,int> loc(xLoc,zLoc);
    chunkMap.insert(std::pair<std::tuple<int,int>,int>(loc,chunkCounter));
    chunkCounter++;

    PerlinNoise perlinNoise;
    for (int i = 0; i < chunkWidth; ++i) {
        for (int j = 0; j <chunkLength; ++j) {
            double z = (double)j/(double)chunkLength;
            double x = (double)i/(double)chunkWidth;
            double y = perlinNoise.noise(x,z,0.6);
            blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,y*100,zLoc*chunkLength*2+j*2),"cobble",chunkCounter);
            //blockManager.AddBlock(glm::vec3(i*2,y*20,j*2),"cobble",chunkCounter);
        }
    }

}

void TerrainGenerator::Update() {

}
