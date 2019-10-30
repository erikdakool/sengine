//
// Created by erik on 18.10.2019.
//

#include "Triangle.h"

Triangle::Triangle() {

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

Triangle::~Triangle() {

}

void Triangle::Draw(Camera& camera) {
    glm::mat4 Projection = camera.getPerspectiveMatrix();
    glm::mat4 View       = camera.getViewMatrix();
    glm::mat4 Model      = transform.getTransformMatrix();

    glm::mat4 mvp = Projection * View * Model;

    glUniformMatrix4fv(camera.getMatrixId(),1,GL_FALSE, &mvp[0][0]);

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
    glDeleteBuffers(0, &vertexbuffer);
}