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


    colors.push_back(glm::vec3(.0,1.,0.0));
    colors.push_back(glm::vec3(.0,1.,0.0));
    colors.push_back(glm::vec3(.0,1.,0.0));
    colors.push_back(glm::vec3(.0,1.,0.0));
    colors.push_back(glm::vec3(.0,0.,1.0));
    colors.push_back(glm::vec3(.0,0.,1.0));
    colors.push_back(glm::vec3(.0,0.,1.0));
    colors.push_back(glm::vec3(.0,0.,1.0));

   // calculatePoints();
}

Block::Block(glm::vec3 pos,int offset)
:Block()
{
    this->pos =pos;
    calculatePoints(offset);
}

Block::~Block() {

}

float *Block::getAllVertices() {
    float vert[faces.size()*12];
    for (int i = 0; i < faces.size(); ++i) {
        for (int j = 0; j < 12; ++j) {
            vert[i*j+j] = faces.at(i).vertices.at(j);
        }
    }
    return vert;
}

unsigned int *Block::getAllIndices() {
    unsigned int indices[faces.size()*6];
    for (int i = 0; i < faces.size(); ++i) {
        for (int j = 0; j < 6; ++j) {
            indices[i*j+j] = faces.at(i).vertices.at(j);
        }
    }
    return indices;
}

void Block::calculatePoints(int offset) {
    vertices.clear();
    indices.clear();
    for (int i = 0; i < faces.size(); ++i) {
        for (int j = 0; j < faces.at(i).indices.size(); ++j) {
            std::vector<glm::vec3>::iterator it;
            it = std::find(vertices.begin(),vertices.end(),squareVertices.at(faces.at(i).indices.at(j))+pos);
            if(it!=vertices.end()){
                indices.push_back(it-vertices.begin()+offset);
            }else{
                vertices.push_back(squareVertices.at(faces.at(i).indices.at(j))+pos);
                indices.push_back(vertices.size()-1+offset);
            }
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
    return ret;}
