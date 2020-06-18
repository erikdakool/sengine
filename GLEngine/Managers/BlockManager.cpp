//
// Created by erikdesk on 5/28/20.
//

#include "BlockManager.h"

#include "shader.hpp"
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL

BlockManager::BlockManager(GameDataRef data) {
    _data = data;

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

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,grassId);
    GLint sampler = glGetUniformLocation(_data->camera.programID,"u_Textures[0]");
    glUniform1i(sampler,0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,dirtId);
    sampler = glGetUniformLocation(_data->camera.programID,"u_Textures[1]");
    glUniform1i(sampler,1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D,stoneId);
    sampler = glGetUniformLocation(_data->camera.programID,"u_Textures[2]");
    glUniform1i(sampler,2);

    glBindVertexArray(vertexArrayID);
    glDrawElements(GL_TRIANGLES, indiceCounter,GL_UNSIGNED_INT, (void*)0);
    //glDrawRangeElements(GL_TRIANGLES,0,indiceCounter,indiceCounter,GL_UNSIGNED_INT,(void*)0);
}

uint64_t BlockManager::AddBlock(glm::vec3 position, std::string textureId, uint64_t chunk,BlockType type) {
    Block block(position,indiceCounter);
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

    grassId = _data->textureLoader.loadBMPTexture("grass2","Data/Textures/textureMap.bmp",0,0,32,32,0);
    //GLint sampler = glGetUniformLocation(_data->camera.programID,"u_Textures[0]");
    //glUniform1i(sampler,0);

    dirtId = _data->textureLoader.loadBMPTexture("dirt1","Data/Textures/textureMap.bmp",1,0,32,32,1);
    //sampler = glGetUniformLocation(_data->camera.programID,"u_Textures[1]");
    //glUniform1i(sampler,1);
    stoneId = _data->textureLoader.loadBMPTexture("dirt2","Data/Textures/textureMap.bmp",2,0,32,32,2);
    //sampler = glGetUniformLocation(_data->camera.programID,"u_Textures[2]");
    //glUniform1i(sampler,2);
}

void BlockManager::RemoveBlock(uint64_t id) {

}

void BlockManager::ClearBlocks() {

}
