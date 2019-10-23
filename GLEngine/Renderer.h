//
// Created by erik on 22.10.2019.
//

#ifndef GLENGINE_RENDERER_H
#define GLENGINE_RENDERER_H

#include <vector>

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "VboIndex.h"
#include "Camera.h"
#include "Managers.h"
#include "Transform.h"

class Renderer {
public:
    Renderer(GameDataRef data);
    ~Renderer();
    void Draw();
    Transform transform = Transform();

private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    GameDataRef _data;

    GLuint vertexbuffer;
    GLuint uvbuffer;

};


#endif //GLENGINE_RENDERER_H
