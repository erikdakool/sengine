//
// Created by erikdesk on 6/2/20.
//
#include <algorithm>
#include "Block.h"

Block::Block() {
    squareVertices.push_back(glm::vec3(-1.0, -1.0,  1.0));
    squareVertices.push_back(glm::vec3(1.0, -1.0,  1.0));
    squareVertices.push_back(glm::vec3(1.0, 1.0,  1.0));
    squareVertices.push_back(glm::vec3(-1.0, 1.0,  1.0));

    squareVertices.push_back(glm::vec3(-1.0, -1.0,  -1.0));
    squareVertices.push_back(glm::vec3(1.0, -1.0,  -1.0));
    squareVertices.push_back(glm::vec3(1.0, 1.0,  -1.0));
    squareVertices.push_back(glm::vec3(-1.0, 1.0,  -1.0));

    faces.push_back(Face(UP));
    faces.push_back(Face(DOWN));
    faces.push_back(Face(FRONT));
    faces.push_back(Face(BACK));
    faces.push_back(Face(LEFT));
    faces.push_back(Face(RIGHT));


    squareColors.push_back(glm::vec4(.0, 1., 0.0,1.0));
    squareColors.push_back(glm::vec4(.0, 1., 0.0,1.0));
    squareColors.push_back(glm::vec4(.0, 1., 0.0,1.0));
    squareColors.push_back(glm::vec4(.0, 1., 0.0,1.0));
    squareColors.push_back(glm::vec4(.0, 0., 1.0,1.0));
    squareColors.push_back(glm::vec4(.0, 0., 1.0,1.0));
    squareColors.push_back(glm::vec4(.0, 0., 1.0,1.0));
    squareColors.push_back(glm::vec4(.0, 0., 1.0,1.0));

   // calculatePoints();
}

Block::Block(glm::vec3 pos,int offset)
:Block()
{
    this->pos =pos;
    calculatePoints(offset);
}

Block::Block(glm::vec3 pos,int offset, BlockType type)
:Block()
{
    this->pos =pos;

    squareColors.clear();
    switch (type) {
        case Grass:

            squareColors.push_back(glm::vec4(.8,.4,.0,1.0));
            squareColors.push_back(glm::vec4(.8,.4,.0,1.0));
            squareColors.push_back(glm::vec4(.0, 1., 0.0,1.0));
            squareColors.push_back(glm::vec4(.0, 1., 0.0,1.0));
            squareColors.push_back(glm::vec4(.8,.4,.0,1.0));
            squareColors.push_back(glm::vec4(.8,.4,.0,1.0));
            squareColors.push_back(glm::vec4(.0, 1., 0.0,1.0));
            squareColors.push_back(glm::vec4(.0, 1., 0.0,1.0));
            break;
        case Stone:
            squareColors.push_back(glm::vec4(.128, .128, 0.128,1.0));
            squareColors.push_back(glm::vec4(.128, .128, 0.128,1.0));
            squareColors.push_back(glm::vec4(.160, .160, 0.160,1.0));
            squareColors.push_back(glm::vec4(.128, .128, 0.128,1.0));
            squareColors.push_back(glm::vec4(.32, .32, 0.32,1.0));
            squareColors.push_back(glm::vec4(.32, .32, 0.32,1.0));
            squareColors.push_back(glm::vec4(.160, .160, 0.160,1.0));
            squareColors.push_back(glm::vec4(.32, .32, 0.32,1.0));
            break;
        case Dirt:
            squareColors.push_back(glm::vec4(.8,.4,.0,1.0));
            squareColors.push_back(glm::vec4(.8,.4,.0,1.0));
            squareColors.push_back(glm::vec4(1., .8, 0.5,1.0));
            squareColors.push_back(glm::vec4(.8,.4,.0,1.0));
            squareColors.push_back(glm::vec4(1., .5, 0.,1.0));
            squareColors.push_back(glm::vec4(1., .5, 0.,1.0));
            squareColors.push_back(glm::vec4(1., .8, 0.5,1.0));
            squareColors.push_back(glm::vec4(1., .5, 0.,1.0));
            break;
        case Water:
            squareColors.push_back(glm::vec4(.3,1,1,1.0));
            squareColors.push_back(glm::vec4(.3,1,1,1.0));
            squareColors.push_back(glm::vec4(.2,.7,1,1.0));
            squareColors.push_back(glm::vec4(.3,1,1,1.0));
            squareColors.push_back(glm::vec4(.3,.55,1,1.0));
            squareColors.push_back(glm::vec4(.3,.55,1,1.0));
            squareColors.push_back(glm::vec4(.2,.7,1,1.0));
            squareColors.push_back(glm::vec4(.3,.55,1,1.0));
            break;
        case Snow:
            squareColors.push_back(glm::vec4(1,1,1,1.0));
            squareColors.push_back(glm::vec4(1,1,1,1.0));
            squareColors.push_back(glm::vec4(1,1,1,1.0));
            squareColors.push_back(glm::vec4(1,1,1,1.0));
            squareColors.push_back(glm::vec4(1,1,1,1.0));
            squareColors.push_back(glm::vec4(1,1,1,1.0));
            squareColors.push_back(glm::vec4(1,1,1,1.0));
            squareColors.push_back(glm::vec4(1,1,1,1.0));
            break;
    }

    calculatePoints(offset);
}



Block::~Block() {

}

void Block::calculatePoints(int offset) {
    vertices.clear();
    indices.clear();
    textureCor.clear();
    for (int i = 0; i < faces.size(); ++i) {
        for (int j = 0; j < faces.at(i).indices.size(); ++j) {
            std::vector<glm::vec3>::iterator it;
            it = std::find(vertices.begin(),vertices.end(),squareVertices.at(faces.at(i).indices.at(j))+pos);
            if(it!=vertices.end()){
                indices.push_back(it-vertices.begin()+offset);
            }else{
                vertices.push_back(squareVertices.at(faces.at(i).indices.at(j))+pos);
                colors.push_back(squareColors.at(faces.at(i).indices.at(j)));
                indices.push_back(vertices.size()-1+offset);
            }
        }
        for (int k = 0; k < faces.at(i).texturePos.size(); k+=2) {
            glm::vec2 t;
            t.x = faces.at(i).texturePos.at(k);
            t.y = faces.at(i).texturePos.at(k+1);
            textureCor.push_back(t);
        }
    }
}

std::vector<float> Block::getAllVerticesV() {
    std::vector<float> ret;
    for (int j = 0; j < vertices.size(); ++j) {
        ret.push_back(vertices.at(j).x);
        ret.push_back(vertices.at(j).y);
        ret.push_back(vertices.at(j).z);
    }
    return ret;
}

std::vector<unsigned int> Block::getAllIndicesV() {
    return indices;
}

std::vector<float> Block::getAllColorsV() {
    std::vector<float> ret;
    for (int j = 0; j < colors.size(); ++j) {
        ret.push_back(colors.at(j).x);
        ret.push_back(colors.at(j).y);
        ret.push_back(colors.at(j).z);
    }
    return ret;
}

std::vector<float> Block::getAllTexturePosV() {
    std::vector<float> ret;
    for (int j = 0; j < textureCor.size(); ++j) {
        ret.push_back(textureCor.at(j).x);
        ret.push_back(textureCor.at(j).y);
    }
    return ret;
}
