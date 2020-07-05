//
// Created by erikdesk on 5/29/20.
//

#include "TerrainGenerator.h"

#include <cmath>
#include "PerlinNoise.h"
#include "../StaticMethods/PointMath.h"

TerrainGenerator::TerrainGenerator(GameDataRef data)
{
    this->data = data;

    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 24; ++j) {
            auto manager = std::make_shared<ChunkManager>(data, *this,i,0,j);
            generateChunk(i,j,manager);
            insertChunkManager(manager,i,0,j);
        }
    }
    for(auto iter = ChunkMap.begin(); iter !=ChunkMap.end(); ++iter) {
        iter->second->calculateSides();
    }
}

TerrainGenerator::~TerrainGenerator() {

}

void TerrainGenerator::Update() {
    auto pos = data->camera.getPos();
    //std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
    auto rot = data->camera.getRotation();
    auto coneVector = glm::vec2(cos(rot.y*3.141 / 180.0 ),sin(rot.y* 3.141 / 180.0));

    //std::cout << "Rotation: "<< rot.y << std::endl;
    //std::cout << cameraPos.x << " " << cameraPos.y << std::endl;
    //std::cout << "Cone vector" << coneVector.x << " " << coneVector.y << std::endl;
    for(auto & iter : ChunkMap){
        auto loc = iter.first;
        auto locv = glm::vec2(std::get<0>(loc)*16,std::get<2>(loc)*16);


        //std::cout << locv.x << " " << locv.y << std::endl;
        auto playerLoc = glm::vec2(pos.x,pos.z);
        //std::cout << "Angle: " << angle << std::endl;
        if(inRange(playerLoc.x-16,playerLoc.x+16,locv.x) && inRange(playerLoc.y-16,playerLoc.y+16,locv.y)){
            iter.second->Draw();
        }else{
            if(insideFov(rot.y,locv,playerLoc,coneVector) || insideFov(rot.y,glm::vec2(locv.x+16,locv.y+16),playerLoc,coneVector)){
                iter.second->Draw();
            }
        }
    }
}

void TerrainGenerator::generateChunk(int xLoc, int zLoc, std::shared_ptr<ChunkManager> manager) {

    PerlinNoise perlinNoise;
    for (int i = 0; i < chunkWidth; ++i) {
        for (int j =0; j <chunkLength; ++j) {
            double z = (double)j/(double)chunkLength;
            double x = (double)i/(double)chunkWidth;
            double height = perlinNoise.noise(x+xLoc,z+zLoc,hardness);

            int y = (int)(height*heightMulti);
            y = y-5;
            manager->AddBlock(i,y,j,chunkWidth*xLoc,chunkLength*zLoc,1);
            for (int k = 0; k < y; k++) {
                if(y-k>2){
                    manager->AddBlock(i,k,j,chunkWidth*xLoc,chunkLength*zLoc,3);
                }else{
                    manager->AddBlock(i,k,j,chunkWidth*xLoc,chunkLength*zLoc,2);
                }
            }

            //blockManagers[man]->AddBlock(i,y,j,"cobble",chunkCounter,2);
            //blockManagers[man]->AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,y*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,1);
            //blockManagers[man]->AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,y*2-2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,2);
            //blockManagers[man]->AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,y*2-2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,3);
            //blockManagers[man]->AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-1)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Stone);
        }
    }
}

void TerrainGenerator::insertChunkManager(std::shared_ptr<ChunkManager> man, int x, int y, int z) {
    auto mapPos = std::tuple<int,int,int>(x,y,z);
    ChunkMap.emplace(mapPos,man);
}

std::shared_ptr<ChunkManager> TerrainGenerator::GetChunk(int x, int y, int z) {
    auto mapPos = std::tuple<int,int,int>(x,y,z);
    if(ChunkMap.find(mapPos)==ChunkMap.end()){
        return nullptr;
    }
    return ChunkMap.at(mapPos);
}

