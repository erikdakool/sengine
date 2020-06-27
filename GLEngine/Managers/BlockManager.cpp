//
// Created by erikdesk on 5/28/20.
//

#include "BlockManager.h"

#include "shader.hpp"
#include <glm/glm.hpp>
#include <fstream>
#include <json/json.h>


#define GLM_ENABLE_EXPERIMENTAL

BlockManager::BlockManager(GameDataRef data) {
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

BlockManager::~BlockManager() {

}

void BlockManager::Update() {

}

void BlockManager::Draw() {
    glm::mat4 Projection = _data->camera.getPerspectiveMatrix();
    glm::mat4 View       = _data->camera.getViewMatrix();
    //glm::mat4 Model      =  gameobject.transform().getTransformMatrix();

    glm::mat4 mvp = Projection * View;
    glUniformMatrix4fv(_data->camera.getMatrixId(),1,GL_FALSE, &mvp[0][0]);

    glUseProgram(_data->camera.programID);

    auto sampler = glGetUniformLocation(_data->camera.programID,"u_Textures");
    //glUniform1i(sampler,0);
    //sampler = glGetUniformLocation(_data->camera.programID,"u_Textures[1]");
    //glUniform1i(sampler,1);

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

uint64_t BlockManager::AddBlock(glm::vec3 location, std::string textureId, uint64_t chunk, int type) {
    Block block(blockInfo.at(type),location, indiceCounter);
    auto v = block.getAllVertexesV();
    auto c = block.getAllColorsV();
    auto p = block.getAllTexturePosV();
    //vertexes.insert(vertexes.end(),v.begin(),v.end());
    //indices.insert(indices.end(),i.begin(),i.end());
    //colors.insert(colors.end(),c.begin(),c.end());
    //texturePos.insert(texturePos.end(),p.begin(),p.end());
    blocks.push_back(block);

    auto ver = block.getAllVertices(indices.size());
    auto i = block.getAllIndicesV(indices.size());

    vertices.insert(vertices.end(),ver.begin(),ver.end());

    indices.insert(indices.end(),i.begin(),i.end());
    indiceCounter+=indices.size();

    //int e = 0;
    //for (int j = 0; j < 8; ++j) {
    //    for (int k = 0; k < 9; ++k) {
    //        std::cout << ver[e] << " ";
    //        e++;
    //    }
    //    std::cout << std::endl;
    //}

    //for (int l = 0; l < 36; ++l) {
    //    std::cout << i[l] << " ";
    //}
    //std::cout << std::endl;


    updateBuffer();
    return idCounter;
}

void BlockManager::updateBuffer() {
    //std::cout << "Buffer length " << vertices.size() << std::endl;

    ///OpenGL buffer inserts
    glUseProgram(_data->camera.programID);

    //auto loc = glGetUniformLocation(_data->camera.programID,"u_Textures");
    //int samplers[3] = {0,1,2};
    ////glUniform1iv(loc,3,samplers);
    //glUniform1i(loc,01);
    //glClearColor(0.1,0.1,0.1,1);

    //float vert[] = {
    //        -1,-1,0,1,1,1,0,0,0.f,
    //        1,-1,0,1,1,1,1,0,0.f,
    //        1,1,0,1,1,1,1,1,0.f,
    //        -1,1,0,1,1,1,0,1,0.f,

    //        -4,-1,0,1,1,1,0,0,1.0f,
    //        -2,-1,0,1,1,1,1,0,1.0f,
    //        -2,1,0,1,1,1,1,1,1.0f,
    //        -4,1,0,1,1,1,0,1,1.0f,

    //        4,-1,0,1,1,1,0,0,2.0f,
    //        6,-1,0,1,1,1,1,0,2.0f,
    //        6,1,0,1,1,1,1,1,2.0f,
    //        4,1,0,1,1,1,0,1,2.0f
    //};

    //unsigned int ind[] = {
    //        0,1,2,2,3,0,
    //        4,5,6,6,7,4,
    //        8,9,10,10,11,8
    //};

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
    for(auto tex : textureInfo){
        textures[tex.id] = _data->textureLoader.loadBMPTexture(tex.name,"Data/Textures/textureMap2.bmp",tex.x,tex.y,128,128,tex.id);
    }
}

void BlockManager::RemoveBlock(uint64_t id) {

}

void BlockManager::ClearBlocks() {

}
