//
// Created by erik on 22.10.2019.
//

#include "Renderer.h"
#include "../Gameobject/Gameobject.h"
Renderer::Renderer(Gameobject& gameobject,GameDataRef data):
Component(gameobject,data)
{
    std::shared_ptr<ModelStruct> model = _data->modelLoader.LoadOBJ(this->name,"Data/Excavator/tracks.obj");
    _data->textureLoader.loadBMPTexture(this->tname,"Data/cobble3x3.bmp");

    vertices = model->vertices;
    uvs = model->uvs;
    normals = model->normals;
    indexVBO(vertices,uvs,indices,indexed_vertices,indexed_uvs);

}

Renderer::Renderer(Gameobject& gameobject,GameDataRef data,std::string name, std::string url):
Component(gameobject,data)
{
    this->name = name;
    std::shared_ptr<ModelStruct> model = _data->modelLoader.LoadOBJ(name,url);

    _data->textureLoader.loadBMPTexture(this->tname,"Data/Textures/textureMap.bmp");

    vertices = model->vertices;
    uvs = model->uvs;
    normals = model->normals;
    indexVBO(vertices,uvs,indices,indexed_vertices,indexed_uvs);

}

Renderer::Renderer(Gameobject &gameobject, GameDataRef data, std::string name, std::string url, std::string tname, std::string turl):
Component(gameobject,data)
{
    this->name = name;
    std::shared_ptr<ModelStruct> model = _data->modelLoader.LoadOBJ(name,url);

    this->tname = tname;
    _data->textureLoader.loadBMPTexture(this->tname,turl);

    vertices = model->vertices;
    uvs = model->uvs;
    normals = model->normals;
    indexVBO(vertices,uvs,indices,indexed_vertices,indexed_uvs);
}


Renderer::~Renderer() {

}

void Renderer::update(float deltaT) {
    drawIndexed();
}

void Renderer::draw() {
    glm::mat4 Projection = _data->camera.getPerspectiveMatrix();
    glm::mat4 View       = _data->camera.getViewMatrix();
    glm::mat4 Model      =  gameobject.transform().getTransformMatrix();

    glm::mat4 mvp = Projection * View * Model;

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(uvs[0]), &uvs[0], GL_STATIC_DRAW);

    glUniformMatrix4fv(_data->camera.getMatrixId(),1,GL_FALSE, &mvp[0][0]);

    GLuint TextureID  = glGetUniformLocation(_data->camera.programID, "myTextureSampler");
    GLuint Texture = _data->textureLoader.getTextureID("toe");

    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);

    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID, 0);

    // 1rst attribute buffer : squareVertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
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
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(
            1,                                // attribute
            2,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDeleteBuffers(1,&vertexbuffer);
    glDeleteBuffers(1,&uvbuffer);
}

void Renderer::drawIndexed() {
    glm::mat4 Projection = _data->camera.getPerspectiveMatrix();
    glm::mat4 View       = _data->camera.getViewMatrix();
    glm::mat4 Model      =  gameobject.transform().getTransformMatrix();

    glm::mat4 mvp = Projection * View * Model;

    vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(indexed_vertices[0]), &indexed_vertices[0], GL_STATIC_DRAW);

    uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(indexed_uvs[0]), &indexed_uvs[0], GL_STATIC_DRAW);

    // Generate a buffer for the indices as well
    GLuint elementbuffer;
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);

    glUniformMatrix4fv(_data->camera.getMatrixId(),1,GL_FALSE, &mvp[0][0]);

    GLuint TextureID  = glGetUniformLocation(_data->camera.programID, "myTextureSampler");
    GLuint Texture = _data->textureLoader.getTextureID(this->tname);

    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glBindTexture(GL_TEXTURE_2D, Texture);

    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID, 0);

    // 1rst attribute buffer : squareVertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
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
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(
            1,                                // attribute
            2,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    // Draw the triangles !
    glDrawElements(
            GL_TRIANGLES,      // mode
            indices.size(),    // count
            GL_UNSIGNED_SHORT,   // type
            (void*)0           // element array buffer offset
    );
    // Draw the triangle !
    //glDrawArrays(GL_TRIANGLES, 0, squareVertices.size() );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDeleteBuffers(1,&vertexbuffer);
    glDeleteBuffers(1,&uvbuffer);
}