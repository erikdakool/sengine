//
// Created by erikdesk on 5/29/20.
//

#include "TerrainGenerator.h"

#include <cmath>
#include <zconf.h>
#include <mutex>
#include <future>
#include <map>

#include "PerlinNoise.h"
#include "../StaticMethods/PointMath.h"

#define RANGE 16

static std::mutex calculationMutex;
static std::shared_ptr<ChunkManager> CalculatePointsAsync(std::shared_ptr<ChunkManager> pendingChunk ){
    pendingChunk->calculateSides();
    return pendingChunk;
    std::lock_guard<std::mutex> lock(calculationMutex);
    auto mapPos = pendingChunk->getChunkLoc();
    //std::cout << managers->size() << std::endl;

    //std::cout << managers->size() << std::endl;
}

static std::mutex chunkAddMutex;
static void AddChunks(std::map<std::tuple<int,int,int>,std::shared_ptr<ChunkManager>>* managers, const std::shared_ptr<ChunkManager>& chunk){
    chunk->calculateSides();
    //auto pend = std::async(std::launch::async,CalculatePointsAsync,chunk.second);
    chunk->pendingOpengl = true;
    auto loc = chunk->getChunkLoc();
    std::lock_guard<std::mutex> lock(chunkAddMutex);
    managers->emplace(loc,chunk);
}

static void CalculatePoints(std::map<std::tuple<int,int,int>,std::shared_ptr<ChunkManager>>* managers, const std::shared_ptr<ChunkManager>& pendingChunk ){
    pendingChunk->calculateSides();
    auto mapPos = pendingChunk->getChunkLoc();
    pendingChunk->pendingOpengl = true;
    managers->emplace(mapPos,pendingChunk);
}

TerrainGenerator::TerrainGenerator(GameDataRef data)
{
    this->data = data;

    auto pos = data->camera.getPos();
    CurrentChunk = {pos.x/16,pos.y/16,pos.z/16};

    for (int i = std::get<0>(CurrentChunk)-RANGE;  i <= std::get<0>(CurrentChunk) + RANGE; ++i) {
        for (int j = std::get<2>(CurrentChunk)-RANGE; j <= std::get<2>(CurrentChunk) + RANGE; ++j) {
            auto manager = std::make_shared<ChunkManager>(data, *this,i,0,j);
            generateChunk(i,j,manager);
            ChunkMap.emplace(std::tuple<int,int,int>{i,0,j},manager);
            auto loc = manager->getChunkLoc();
            PendingChunks.emplace(loc,manager);
            //insertChunkManager(manager,i,0,j);
        }
    }
    for(auto & iter : PendingChunks) {
        //std::cout << std::get<0>(iter.first) << " " << std::get<2>(iter.first) << std::endl;
        //iter.second->calculateSides();
        //CalculatePoints(&ChunkMap, iter);
        //futures.push_back(std::async(std::launch::async,CalculatePointsAsync,&ChunkMap,iter));
        futures.push_back(std::async(std::launch::async,AddChunks,&RenderList,iter.second));
    }
    PendingChunks.clear();
}

TerrainGenerator::~TerrainGenerator() {

}

void TerrainGenerator::Update() {
    auto pos = data->camera.getPos();
    //std::cout << pos.x << " " << pos.z << std::endl;

    int x = (int)pos.x/16;
    int y = (int)pos.z/16;
    bool change= false;
    int xDiff = x - std::get<0>(CurrentChunk);
    if(xDiff == 1) {
        change = true;
        for (auto iter = RenderList.begin(); iter != RenderList.end();) {
            int locX = std::get<0>(iter->first);
            if (locX < x - RANGE) {
                auto manager = std::make_shared<ChunkManager>(data, *this, x + RANGE, 0, std::get<2>(iter->first));
                generateChunk(x + RANGE, std::get<2>(iter->first), manager);
                auto loc = manager->getChunkLoc();
                PendingChunks.emplace(loc,manager);
                iter->second->deleteBuffers();
                iter = RenderList.erase(iter);
            } else {
                ++iter;
            }
        }
        std::get<0>(CurrentChunk) += xDiff;
    }
    else if (xDiff ==-1) {
        change = true;
        for (auto iter = RenderList.begin(); iter != RenderList.end();) {
            int locX = std::get<0>(iter->first);
            if (locX > x + RANGE) {
                auto manager = std::make_shared<ChunkManager>(data, *this, x - RANGE, 0, std::get<2>(iter->first));
                generateChunk(x - RANGE, std::get<2>(iter->first), manager);
                auto loc = manager->getChunkLoc();
                PendingChunks.emplace(loc,manager);
                iter->second->deleteBuffers();
                iter = RenderList.erase(iter);
            } else {
                ++iter;
            }
        }
        std::get<0>(CurrentChunk) += xDiff;
    }

    int yDiff = y - std::get<2>(CurrentChunk);
    if(yDiff == 1) {
        change = true;
        for (auto iter= RenderList.begin(); iter!=RenderList.end();) {
            int locY = std::get<2>(iter->first);
            if(locY < y-RANGE){
                auto manager = std::make_shared<ChunkManager>(data, *this,std::get<0>(iter->first),0,y+RANGE);
                generateChunk(std::get<0>(iter->first),y+RANGE,manager);
                auto loc = manager->getChunkLoc();
                PendingChunks.emplace(loc,manager);
                iter->second->deleteBuffers();
                iter = RenderList.erase(iter);
            }else{
                ++iter;
            }
        }
        std::get<2>(CurrentChunk) += yDiff;
    }
    else if (yDiff ==-1){
        change = true;
        for (auto iter= RenderList.begin(); iter!=RenderList.end();) {
            int locY = std::get<2>(iter->first);
            if(locY > y+RANGE){
                auto manager = std::make_shared<ChunkManager>(data, *this,std::get<0>(iter->first),0,y-RANGE);
                generateChunk(std::get<0>(iter->first),y-RANGE,manager);
                auto loc = manager->getChunkLoc();
                PendingChunks.emplace(loc,manager);
                iter->second->deleteBuffers();
                iter = RenderList.erase(iter);
            }else{
                ++iter;
            }
        }
        std::get<2>(CurrentChunk) += yDiff;
    }


    if(change){
        for(auto & iter : PendingChunks) {
         futures.push_back(std::async(std::launch::async, AddChunks, &RenderList, iter.second));
        }
        PendingChunks.clear();
    }

    auto rot = data->camera.getRotation();
    auto coneVector = glm::vec2(cos(rot.y*3.141 / 180.0 ),sin(rot.y* 3.141 / 180.0));

    //std::cout << "Rotation: "<< rot.y << std::endl;
    //std::cout << cameraPos.x << " " << cameraPos.y << std::endl;
    //std::cout << "Cone vector" << coneVector.x << " " << coneVector.y << std::endl;
    //std::cout << RenderList.size() << std::endl;
    for(auto & iter : RenderList){
        if(iter.second->pendingOpengl){
            iter.second->deleteBuffers();
            iter.second->updateBuffer();
            iter.second->pendingOpengl = false;
        }


        auto loc = iter.second->getChunkLoc();
        auto locv = glm::vec2(std::get<0>(loc)*CHUNKSIZE*2,std::get<2>(loc)*CHUNKSIZE*2);

        //std::cout << locv.x << " " << locv.y << std::endl;
        auto playerLoc = glm::vec2(pos.x,pos.z);
        //std::cout << "Angle: " << angle << std::endl;
        if(inRange(playerLoc.x-CHUNKSIZE*2,playerLoc.x+CHUNKSIZE*2,locv.x) && inRange(playerLoc.y-CHUNKSIZE*2,playerLoc.y+CHUNKSIZE*2,locv.y)){
            iter.second->Draw();
        }else{
            if(insideFov(rot.y,locv,playerLoc,coneVector) || insideFov(rot.y,glm::vec2(locv.x+CHUNKSIZE*2,locv.y+CHUNKSIZE*2),playerLoc,coneVector)){
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

int TerrainGenerator::getCount() {
    return PendingChunks.size();
}