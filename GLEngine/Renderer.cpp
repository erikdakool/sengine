//
// Created by erik on 22.10.2019.
//

#include "Renderer.h"

Renderer::Renderer(GameDataRef data) {
    _data = data;
    std::shared_ptr<ModelStruct> model = _data->modelLoader.LoadOBJ("noe","Data/suzanne.obj");

    vertices = model->vertices;
    uvs = model->uvs;
    normals = model->normals;

    _data->textureLoader.loadBMPTexture("toe","Data/cobble.bmp");
}

Renderer::~Renderer() {

}

void Renderer::Draw() {
    glm::mat4 Projection = _data->camera.getPerspectiveMatrix();
    glm::mat4 View       = _data->camera.getViewMatrix();
    glm::mat4 Model      = transform.getTransformMatrix();

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

    // 1rst attribute buffer : vertices
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
}