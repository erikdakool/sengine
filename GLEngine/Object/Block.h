//
// Created by erikdesk on 5/28/20.
//

#ifndef GLENGINE_BLOCK_H
#define GLENGINE_BLOCK_H

#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "../Structs/BlockInfo.h"
#include "../Structs/Face.h"

class Block{
public:
    Block(BlockInfo blockInfo);
    Block(BlockInfo blockInfo, glm::vec3 pos,int offset,int type);
    Block(BlockInfo blockInfo, glm::vec3 pos,int offset);
    ~Block();

    std::vector<float> getAllVertices(int offset);
    std::vector<float> getAllVertexesV();
    std::vector<float> getAllColorsV();
    std::vector<unsigned int> getAllIndicesV(int offset);
    std::vector<float> getAllTexturePosV();
private:
    void calculatePoints(int offset);
    std::vector<Face> faces;

    std::vector<glm::vec3> squareVertices;
    std::vector<glm::vec4> squareColors;
    std::vector<glm::vec2> textureCor;
    std::vector<glm::vec3> vertices;

    std::vector<unsigned int> indices;
    std::vector<glm::vec4> colors;
    std::vector<float> textureId;
    std::vector<float> verticesV;

    glm::vec3 pos = glm::vec3(0,0,0);
};

#endif //GLENGINE_BLOCK_H
