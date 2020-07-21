//
// Created by erikdesk on 5/28/20.
//

#include "ChunkManager.h"

#include "shader.hpp"
#include <glm/glm.hpp>
#include <fstream>
#include <json/json.h>
#include "shader.hpp"
#include "TerrainGenerator.h"

#define GLM_ENABLE_EXPERIMENTAL


ChunkManager::ChunkManager(GameDataRef data,TerrainGenerator& terrainGenerator, int x, int y, int z)
:terrainGenerator(terrainGenerator)
{
    //ChunkBlocks.resize(16);
    //for (int j = 0; j < 16; ++j) {
    //    ChunkBlocks[j].resize(16);
    //    for (int i = 0; i < 16; ++i) {
    //        ChunkBlocks[j][i].resize(16);
    //    }
    //}

    chunkLoc = std::tuple<int,int,int>(x,y,z);

    _data = data;

    std::ifstream block_File("Data/Json/block.json");
    std::ifstream textures_File("Data/Json/textures.json");

    Json::Value textureInfo;
    textures_File >> textureInfo;

    for(Json::Value::ArrayIndex i = 0; i != textureInfo.size(); i++) {
        TextureInfo tex;
        tex.x = textureInfo[i]["x"].asInt();
        tex.y = textureInfo[i]["y"].asInt();
        tex.id = textureInfo[i]["id"].asInt();
        tex.name = textureInfo[i]["name"].asString();
        this->textureInfo.push_back(tex);
    }


    Json::Value blockInfo;
    block_File >> blockInfo;

    for(Json::Value::ArrayIndex i = 0; i != blockInfo.size(); i++){
        BlockInfo block;
        block.id = blockInfo[i]["id"].asInt();
        block.name = blockInfo[i]["name"].asString();
        block.left = blockInfo[i]["left"].asInt();
        block.right = blockInfo[i]["right"].asInt();
        block.front = blockInfo[i]["front"].asInt();
        block.back = blockInfo[i]["back"].asInt();
        block.top = blockInfo[i]["top"].asInt();
        block.bottom = blockInfo[i]["bottom"].asInt();
        this->blockInfo.push_back(block);
    }
}

ChunkManager::~ChunkManager() {

}

void ChunkManager::Update() {

}

void ChunkManager::Draw() {
    glm::mat4 Projection = _data->camera.getPerspectiveMatrix();
    glm::mat4 View       = _data->camera.getViewMatrix();
    //glm::mat4 Model      =  gameobject.transform().getTransformMatrix();

    glUseProgram(_data->camera.getBlockProgramId());

    glm::mat4 mvp = Projection * View;
    glUniformMatrix4fv(_data->camera.getBlockMatrixId(),1,GL_FALSE, &mvp[0][0]);

    auto sampler = glGetUniformLocation(_data->camera.getBlockProgramId(),"u_Textures");

    int samplers[texturesCount];
    for (int j = 0; j < texturesCount; ++j) {
        samplers[j] = j;
    }
    glUniform1iv(sampler, texturesCount, samplers);

    for (int i = 0; i < texturesCount; ++i) {
        glActiveTexture(GL_TEXTURE0+i);
        glBindTexture(GL_TEXTURE_2D,this->textures[i]);
    }

    auto units = GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS;

    glBindVertexArray(vertexArrayID);
    //glDrawElements(GL_TRIANGLES, indiceCounter,GL_UNSIGNED_INT, (void*)0);
    glDrawRangeElements(GL_TRIANGLES,0,indiceCounter,indiceCounter,GL_UNSIGNED_INT,(void*)0);
}

uint64_t ChunkManager::AddBlock(int x, int y, int z, int chunkXoffset, int chunkYoffset, int type) {
    auto pos = glm::vec3((x + chunkXoffset) * 2, y * 2, (z + chunkYoffset) * 2);

    auto block = std::make_shared<Block>(blockInfo.at(type),pos, indiceCounter);

    auto mapPos = std::tuple<int,int,int>(x,y,z);
    ChunkBlocks.emplace(mapPos,block);

    auto v = block->getAllVertexesV();
    auto c = block->getAllColorsV();
    auto p = block->getAllTexturePosV();

    return idCounter;
}

void ChunkManager::calculateSides() {
    indiceCounter = 0;
    indices.clear();
    vertices.clear();
    for (int x = 0; x < chunkSize; ++x) {
        for (int y = 0; y < chunkSize; ++y) {
            for (int z = 0; z < chunkSize; ++z) {
                auto block = getBlock(x,y,z);
                if(block!= nullptr){
                    block->clearFaces();
                    if(x==0){
                     auto chunk = terrainGenerator.GetChunk(std::get<0>(chunkLoc)-1,std::get<1>(chunkLoc),std::get<2>(chunkLoc));
                         if(chunk!= nullptr){
                             if(!chunk->getBlockExists(chunkSize-1,y,z)){
                                 block->addFace(LEFT);
                             }
                         }
                    }
                    else if (!getBlockExists(x-1,y,z)) {
                        block->addFace(LEFT);
                    }

                    if(x==chunkSize-1){
                        auto chunk = terrainGenerator.GetChunk(std::get<0>(chunkLoc)+1,std::get<1>(chunkLoc),std::get<2>(chunkLoc));
                        if(chunk!= nullptr){
                            if(!chunk->getBlockExists(0,y,z)){
                                block->addFace(RIGHT);
                            }
                        }
                    }else if(!getBlockExists(x+1,y,z)){
                        block->addFace(RIGHT);
                    }

                      if(!getBlockExists(x,y+1,z)){
                          block->addFace(TOP);
                      }
                      if(!getBlockExists(x,y-1,z)){
                          block->addFace(BOTTOM);
                      }

                    if(z==0){
                        auto chunk = terrainGenerator.GetChunk(std::get<0>(chunkLoc),std::get<1>(chunkLoc),std::get<2>(chunkLoc)-1);
                        if(chunk!= nullptr){
                            if(!chunk->getBlockExists(x,y,chunkSize-1)){
                                block->addFace(BACK);
                            }
                        }
                    }else if(!getBlockExists(x,y,z-1)) {
                        block->addFace(BACK);
                    }

                    if(z==chunkSize-1){
                        auto chunk = terrainGenerator.GetChunk(std::get<0>(chunkLoc),std::get<1>(chunkLoc),std::get<2>(chunkLoc)+1);
                        if(chunk!= nullptr){
                            if(!chunk->getBlockExists(x,y,0)){
                                block->addFace(FRONT);
                            }
                        }
                    }else if(!getBlockExists(x,y,z+1)){
                        block->addFace(FRONT);
                    }

                    block->calculatePoints(indiceCounter);
                    auto ver = block->getAllVertices(indices.size());
                    auto i = block->getAllIndicesV(indices.size());

                    vertices.insert(vertices.end(),ver.begin(),ver.end());

                    indices.insert(indices.end(),i.begin(),i.end());
                    indiceCounter+=indices.size();
                }
            }
        }
    }
}

std::shared_ptr<Block> ChunkManager::getBlock(int x, int y, int z) {
    if(getBlockExists(x,y,z)){
        auto mapPos = std::tuple<int,int,int>(x,y,z);
        return ChunkBlocks.at(mapPos);
    }else{
        return nullptr;
    }
}

bool ChunkManager::getBlockExists(int x, int y, int z) {
    if(x>=chunkSize || y>=chunkSize||z>=chunkSize || x<0 || y<0 || z<0){
        return false;
    }
    auto mapPos = std::tuple<int,int,int>(x,y,z);
    return ChunkBlocks.find(mapPos) !=ChunkBlocks.end();
}

void ChunkManager::deleteBuffers() {
    glBindVertexArray(0);
    if(vertexBufferID!=0){
        glDeleteBuffers(1,&vertexBufferID);
    }
    if(indiceBufferID!=0){
        glDeleteBuffers(1,&indiceBufferID);
    }
}

void ChunkManager::updateBuffer() {
    glUseProgram(_data->camera.getBlockProgramId());


    glCreateVertexArrays(1,&vertexArrayID);
    glBindVertexArray(vertexArrayID);

    //Data buffer binding
    glGenBuffers(1,&vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(vertices[0]),&vertices[0],GL_STATIC_DRAW);

    //Indice binding
    glGenBuffers(1,&indiceBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indiceBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(indices[0]),&indices[0],GL_STATIC_DRAW);

    //Vertex attribute binding
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,9*sizeof(float),(void*)0);

    //Color attribute binding
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,9*sizeof(float),(const void*)12);

    //TexturePos attribute binding
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,9*sizeof(float),(const void*)24);

    //Texture attribute binding
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3,1,GL_FLOAT,GL_FALSE,9*sizeof(float),(const void*)32);

    textures.reserve(textureInfo.size());
    for(const auto& tex : textureInfo){
        textures[tex.id] = _data->textureLoader.loadBMPTexture(tex.name,"Data/Textures/textureMap2.bmp",tex.x,tex.y,128,128,tex.id);
    }
}

const std::tuple<int, int, int> &ChunkManager::getChunkLoc() const {
    return chunkLoc;
}

void ChunkManager::setChunkLoc(const std::tuple<int, int, int> &chunkLoc) {
    ChunkManager::chunkLoc = chunkLoc;
}

