//
// Created by erikdesk on 5/29/20.
//

#include "TerrainGenerator.h"

#include <cmath>
#include "PerlinNoise.h"

TerrainGenerator::TerrainGenerator(GameDataRef data)
{
    this->data = data;

    int man =0;
    for (int i = 0; i < 1; ++i) {
        for (int j = 0; j < 1; ++j) {
            blockManagers.push_back(std::make_shared<BlockManager>(data));
            generateChunk(i,j,man);
            man++;
        }
    }
}

TerrainGenerator::~TerrainGenerator() {

}

void TerrainGenerator::Update() {
    for (auto & man : blockManagers){
        man->Draw();
    }
}

void TerrainGenerator::generateChunk(int xLoc, int zLoc, int man) {
    std::tuple<int,int> loc(xLoc,zLoc);
    chunkMap.insert(std::pair<std::tuple<int,int>,int>(loc,chunkCounter));
    chunkCounter++;

    PerlinNoise perlinNoise;
    for (int i = 0; i < chunkWidth; ++i) {
        for (int j =0; j <chunkLength; ++j) {
            double z = (double)j/(double)chunkLength;
            double x = (double)i/(double)chunkWidth;
            double height = perlinNoise.noise(x+xLoc,z+zLoc,hardness);

            int y = (int)(height*heightMulti);
            y = 0;
            blockManagers[man]->AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,y*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,1);
            blockManagers[man]->AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,y*2-2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,2);
            //blockManagers[man]->AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-1)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Stone);
        }
    }

}


