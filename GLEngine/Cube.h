//
// Created by erik on 19.10.2019.
//

#ifndef GLENGINE_CUBE_H
#define GLENGINE_CUBE_H



#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Camera.h"
#include "Transform.h"
#include "AssetController.h"

class Cube {
public:
    Cube(glm::vec3 in, AssetController& assetController);
    ~Cube();
    void Draw(Camera& camera);
    Transform transform = Transform();
private:
    GLfloat g_vertex_buffer_data[36*3];
    GLfloat g_color_buffer_data[36*3];
    GLfloat g_uv_buffer_data[36*3];
    GLuint vertexbuffer;
    GLuint colorbuffer;
    GLuint uvbuffer;
    AssetController& assetController;
};


#endif //GLENGINE_CUBE_H
