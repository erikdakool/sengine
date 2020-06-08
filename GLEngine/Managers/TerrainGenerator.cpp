//
// Created by erikdesk on 5/29/20.
//

#include "TerrainGenerator.h"

#include <cmath>
#include "PerlinNoise.h"

TerrainGenerator::TerrainGenerator(BlockManager& blockManager, GameDataRef data)
:blockManager(blockManager)
{
    this->data = data;

    if(chunkMap.find(std::tuple<int,int>(0,0))==chunkMap.end()){
        for (int i = 0; i < 1; ++i) {
            for (int j = 0; j < 1; ++j) {
                //generateChunk(i,j);
            }
        }
        //generateChunk(-1,-1);
        //generateChunk(-1,0);
        //generateChunk(0,-1);
        generateChunk(0,0);
        //generateChunk(0,-1);
        //generateChunk(1,0);
        //generateChunk(1,1);
        //generateChunk(-1,1);
        //generateChunk(0,1);
        //generateChunk(1,-1);
    }//
}

TerrainGenerator::~TerrainGenerator() {

}

void TerrainGenerator::generateChunk(int xLoc, int zLoc) {
    std::tuple<int,int> loc(xLoc,zLoc);
    chunkMap.insert(std::pair<std::tuple<int,int>,int>(loc,chunkCounter));
    chunkCounter++;

    PerlinNoise perlinNoise;
    for (int i = 0; i < chunkWidth; ++i) {
        for (int j =0; j <chunkLength; ++j) {
            double z = (double)j/(double)chunkLength*12;
            double x = (double)i/(double)chunkWidth*12;
            double height = perlinNoise.noise(x+xLoc,z+zLoc,hardness);

            float distance;
            float distX = abs(i-chunkWidth/2);
            float distZ = abs(j-chunkLength/2);
            distance = std::sqrt((distX*distX)+(distZ*distZ));

            //if(abs(i-128)>(chunkWidth*0.4)/1 || (abs(j-128))>(chunkLength*0.4)/1){
            //   // distance = 30;
            //}else{
            //    //distance= sqrt(abs(i - ((chunkWidth)/2))*(abs(j-((chunkLength+1)/2))));
            //}

            //std::cout << distance << std::endl;

            int y = (int)(height*heightMulti)*2;
            y = y-(distance/3);
            if(y < 35){
                y = 35;
            }
            y =45;
            //Grass
            if(y>55 + 20){
                blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,y*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Snow);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-1)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Stone);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-2)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Stone);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-3)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Stone);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-4)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Stone);
            }
            else if(y> 53+ 16){
                blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,y*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Stone);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-1)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Stone);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-2)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Stone);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-3)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Stone);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-4)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Stone);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-5)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Stone);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-6)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Stone);
            }
            else if(y>37){
                blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,y*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Grass);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-1)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Dirt);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-2)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Dirt);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-3)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Dirt);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-4)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Dirt);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-5)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Dirt);
            }else if(y>=36){
                blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,y*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Dirt);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-1)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Dirt);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-2)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Dirt);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-3)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Dirt);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-4)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Dirt);
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-5)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Dirt);
            }
            else{
                blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,y*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Dirt);
                for (int k = y; k <= 36; k++) {
                    blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,k*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Water);
                }
            }
            //Dirt
            //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-2)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Dirt);
            //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-3)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Dirt);
            //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(y-4)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Dirt);
            //Stone
            for (int k = y-5; k >= 0; k--) {
                //blockManager.AddBlock(glm::vec3(xLoc*chunkWidth*2+i*2,(k)*2,zLoc*chunkLength*2+j*2),"cobble",chunkCounter,Stone);
            }
        }
    }

}

void TerrainGenerator::Update() {
    if(data->inputManager.isKeyPressed(GLFW_KEY_UP)){
        hardness+=.1;
        blockManager.ClearBlocks();
        generateChunk(0,0);
        std::cout << hardness << std::endl;
    }else if(data->inputManager.isKeyPressed(GLFW_KEY_DOWN)){
        hardness-=.1;
        blockManager.ClearBlocks();
        generateChunk(0,0);
        std::cout << hardness << std::endl;
    }
}


