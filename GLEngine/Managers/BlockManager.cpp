//
// Created by erikdesk on 5/28/20.
//

#include "BlockManager.h"

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL

BlockManager::BlockManager(GameDataRef data) {
    _data = data;
    //points[0] = glm::vec3(0,0,0);
    //points[1] = glm::vec3(1,0,0);
    //points[2] = glm::vec3(0,0,1);
    _data->textureLoader.loadBMPTexture("test","Data/uvtemplate.bmp");

    float pre[108] = {
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,

            1.0f, 1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,

            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,

            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,

            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,

            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,

            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,

            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,

            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,

            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,

            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,

            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
    };

    for (int i = 0; i < 36; ++i) {
        points[i] = glm::vec3(pre[3*i],pre[3*i+1],pre[3*i+2]);
    }

    float g_uv_buffer_data[72] = {
            0.000059f, 1.0f-0.000004f,
            0.000103f, 1.0f-0.336048f,
            0.335973f, 1.0f-0.335903f,
            1.000023f, 1.0f-0.000013f,
            0.667979f, 1.0f-0.335851f,
            0.999958f, 1.0f-0.336064f,
            0.667979f, 1.0f-0.335851f,
            0.336024f, 1.0f-0.671877f,
            0.667969f, 1.0f-0.671889f,
            1.000023f, 1.0f-0.000013f,
            0.668104f, 1.0f-0.000013f,
            0.667979f, 1.0f-0.335851f,
            0.000059f, 1.0f-0.000004f,
            0.335973f, 1.0f-0.335903f,
            0.336098f, 1.0f-0.000071f,
            0.667979f, 1.0f-0.335851f,
            0.335973f, 1.0f-0.335903f,
            0.336024f, 1.0f-0.671877f,
            1.000004f, 1.0f-0.671847f,
            0.999958f, 1.0f-0.336064f,
            0.667979f, 1.0f-0.335851f,
            0.668104f, 1.0f-0.000013f,
            0.335973f, 1.0f-0.335903f,
            0.667979f, 1.0f-0.335851f,
            0.335973f, 1.0f-0.335903f,
            0.668104f, 1.0f-0.000013f,
            0.336098f, 1.0f-0.000071f,
            0.000103f, 1.0f-0.336048f,
            0.000004f, 1.0f-0.671870f,
            0.336024f, 1.0f-0.671877f,
            0.000103f, 1.0f-0.336048f,
            0.336024f, 1.0f-0.671877f,
            0.335973f, 1.0f-0.335903f,
            0.667969f, 1.0f-0.671889f,
            1.000004f, 1.0f-0.671847f,
            0.667979f, 1.0f-0.335851f
    };
    for (int i = 0; i < 36; ++i) {
        uvs[i] = glm::vec2(g_uv_buffer_data[2*i],g_uv_buffer_data[2*i+1]);
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

    GLuint buffers;
    GLuint indiceB;

    float vertices[] = {-1, -1, 0, // bottom left corner
                          1, -1, 0, // top left corner
                          1,  1, 0, // top right corner
                          -1, 1, 0}; // bottom right corner

    unsigned int indices[] = {0,1,2,2,3,0};

    glGenBuffers(1,&buffers);
    glBindBuffer(GL_ARRAY_BUFFER,buffers);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),&vertices[0],GL_STATIC_DRAW);

    glGenBuffers(1,&indiceB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indiceB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),&indices[0],GL_STATIC_DRAW);

    GLuint TextureID  = glGetUniformLocation(_data->camera.programID, "myTextureSampler");
    GLuint Texture = _data->textureLoader.getTextureID("test");

    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glBindTexture(GL_TEXTURE_2D, Texture);

    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID, 0);

    // 1rst attribute buffer : vertices
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

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indiceB);
    glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT, (void*)0);

    glDisableVertexAttribArray(0);
    glDeleteBuffers(1,&buffers);
}

uint64_t BlockManager::AddBlock(glm::vec3 position, std::string textureId, uint64_t chunk) {
    Block block;

    block.ChunkId = chunk;
    block.Location = position;
    for (int i = 0; i < 36; ++i) {
        //block.Quad.push_back(points[i]+position);
    }

    for (int j = 0; j < 6; ++j) {
        block.Quad.push_back(block.face.points[j]);
    }

    blocks.push_back(block);

    return idCounter;
}

void BlockManager::RemoveBlock(uint64_t id) {

}
