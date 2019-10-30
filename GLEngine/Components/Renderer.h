//
// Created by erik on 22.10.2019.
//

#ifndef GLENGINE_RENDERER_H
#define GLENGINE_RENDERER_H

#include <vector>

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "../Managers/VboIndex.h"
#include "../Managers.h"
#include "Component.h"

enum Primitive{
    Null = 0,
    Plain = 1,
    //Cube,
    Sphere = 3,
    Pyramid = 4
};

class Renderer : public Component{
public:
    Renderer(Gameobject& gameobject,GameDataRef data);
    ~Renderer();
    void update(float deltaT) override;
    void draw();
    void drawIndexed();

private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;

    std::vector<unsigned short> indices;
    std::vector<glm::vec3> indexed_vertices;
    std::vector<glm::vec2> indexed_uvs;
    std::vector<glm::vec3> indexed_normals;

    GLuint vertexbuffer = 0;
    GLuint uvbuffer = 0;

};


#endif //GLENGINE_RENDERER_H
