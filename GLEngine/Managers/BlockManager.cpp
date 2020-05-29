//
// Created by erikdesk on 5/28/20.
//

#include "BlockManager.h"

BlockManager::BlockManager(GameDataRef data) {
    _data = data;
    //points[0] = glm::vec3(0,0,0);
    //points[1] = glm::vec3(1,0,0);
    //points[2] = glm::vec3(0,0,1);

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
    GLuint buffers[blocks.size()];
    GLuint vao[blocks.size()];
    GLuint uvbuffer[blocks.size()];

    for (int i = 0; i < blocks.size(); ++i) {
        glCreateVertexArrays(1,&vao[i]);
        glBindVertexArray(vao[i]);
        glGenBuffers(1, &buffers[i]);
        glBindBuffer(GL_ARRAY_BUFFER, buffers[i]);
        glBufferData(GL_ARRAY_BUFFER, blocks[i].Quad.size() * sizeof(blocks[i].Quad[0]), &blocks[i].Quad[0], GL_STATIC_DRAW);

        glGenBuffers(1,&uvbuffer[i]);
        glBindBuffer(GL_ARRAY_BUFFER,uvbuffer[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(uvs),uvs,GL_STATIC_DRAW);


        glUniformMatrix4fv(_data->camera.getMatrixId(),1,GL_FALSE, &mvp[0][0]);

        GLuint TextureID  = glGetUniformLocation(_data->camera.programID, "myTextureSampler");
        GLuint Texture = _data->textureLoader.getTextureID("cobble");

        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D, Texture);

        // Set our "myTextureSampler" sampler to use Texture Unit 0
        glUniform1i(TextureID, 0);

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, buffers[i]);
        glVertexAttribPointer(
                0,                  // attribute
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
        );

        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[i]);
        glVertexAttribPointer(
                1,                                // attribute
                2,                                // size
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                (void*)0                          // array buffer offset
        );
        glEnableVertexAttribArray(vao[i]);
    }


    for (int i = 0; i < blocks.size(); ++i) {
        glBindVertexArray(vao[i]);
        glDrawArrays(GL_TRIANGLES, 0, blocks[i].Quad.size() );
        glDisableVertexAttribArray(vao[i]);
    }


    for (int i = 0; i < blocks.size(); ++i) {
        glDeleteBuffers(1,&buffers[i]);
        glDeleteBuffers(1,&uvbuffer[i]);
    }

}

uint64_t BlockManager::AddBlock(glm::vec3 position, std::string textureId) {
    Block block;
    block.Location = position;

    for (int i = 0; i < 36; ++i) {
        block.Quad.push_back(points[i]+position);
    }

    blocks.push_back(block);

    return idCounter;
}

void BlockManager::RemoveBlock(uint64_t id) {

}
