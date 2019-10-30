//
// Created by erik on 18.10.2019.
//

#ifndef GLENGINE_TRIANGLE_H
#define GLENGINE_TRIANGLE_H
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include "../Transform.h"
#include "../Camera.h"

class Triangle {
public:
    Triangle();
    ~Triangle();
    void Draw(Camera& camera);

    Transform transform;
private:
    constexpr static const GLdouble g_vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
    };

    GLuint vertexbuffer;
};


#endif //GLENGINE_TRIANGLE_H
