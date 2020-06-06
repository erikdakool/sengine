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

    GLuint buffers;
    GLuint indiceB;
    GLuint colorB;
    GLuint textureB;
    GLuint texCorB;

    glUseProgram(_data->camera.programID);
    auto loc = glGetUniformLocation(_data->camera.programID,"u_Textures");
    int samplers[3] = {0,1,2};
    glUniform1iv(loc,2,samplers);

    float * textures = new float[vertexes.size()];
    for (int j = 0; j < vertexes.size(); ++j) {
        textures[j] = 2.0f;
    }

    glGenBuffers(1,&buffers);
    glBindBuffer(GL_ARRAY_BUFFER,buffers);
    glBufferData(GL_ARRAY_BUFFER,vertexes.size()*sizeof(vertexes[0]),&vertexes[0],GL_STATIC_DRAW);

    glGenBuffers(1,&indiceB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indiceB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(indices[0]),&indices[0],GL_STATIC_DRAW);

    glGenBuffers(1,&colorB);
    glBindBuffer(GL_ARRAY_BUFFER,colorB);
    glBufferData(GL_ARRAY_BUFFER,colors.size()*sizeof(colors[0]),&colors[0],GL_STATIC_DRAW);

    glGenBuffers(1,&texCorB);
    glBindBuffer(GL_ARRAY_BUFFER,texCorB);
    glBufferData(GL_ARRAY_BUFFER,texturePos.size()*sizeof(texturePos[0]),&texturePos[0],GL_STATIC_DRAW);

    glGenBuffers(1,&textureB);
    glBindBuffer(GL_ARRAY_BUFFER,textureB);
    glBufferData(GL_ARRAY_BUFFER,sizeof(textures),&textures[0],GL_STATIC_DRAW);

    // 1rst attribute buffer : squareVertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, buffers);
    glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,colorB);
    glVertexAttribPointer(
            1,
            4,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
    );

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER,texCorB);
    glVertexAttribPointer(
            2,
            2,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
    );

    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER,textureB);
    glVertexAttribPointer(
            3,
            1,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
    );

    //int vertexColorLocation = glGetUniformLocation(_data->camera.programID, "ourColor");

    //glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);



    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indiceB);
    glDrawElements(GL_TRIANGLES, indices.size(),GL_UNSIGNED_INT, (void*)0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(3);

    glDeleteBuffers(1,&buffers);
    glDeleteBuffers(1,&indiceB);
    glDeleteBuffers(1,&colorB);
    glDeleteBuffers(1,&textureB);

}

uint64_t BlockManager::AddBlock(glm::vec3 position, std::string textureId, uint64_t chunk,BlockType type) {
    Block block(position,vertexes.size()/3,type);
    auto v = block.getAllVerticesV();
    auto i = block.getAllIndicesV();
    auto c = block.getAllColorsV();
    auto p = block.getAllTexturePosV();
    vertexes.insert(vertexes.end(),v.begin(),v.end());
    indices.insert(indices.end(),i.begin(),i.end());
    colors.insert(colors.end(),c.begin(),c.end());
    texturePos.insert(texturePos.end(),p.begin(),p.end());
    blocks.push_back(block);
    return idCounter;
}

void BlockManager::RemoveBlock(uint64_t id) {

}

void BlockManager::ClearBlocks() {
    vertexes.clear();
    indices.clear();
    colors.clear();
    blocks.clear();
}
