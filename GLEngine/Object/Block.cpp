//
// Created by erikdesk on 6/2/20.
//
#include <algorithm>
#include <iostream>
#include "Block.h"

Block::Block(BlockInfo blockInfo):
blockInfo(blockInfo)
{
    squareVertices.push_back(glm::vec3(-1.0, -1.0,  1.0));
    squareVertices.push_back(glm::vec3(1.0, -1.0,  1.0));
    squareVertices.push_back(glm::vec3(1.0, 1.0,  1.0));
    squareVertices.push_back(glm::vec3(-1.0, 1.0,  1.0));

    squareVertices.push_back(glm::vec3(-1.0, -1.0,  -1.0));
    squareVertices.push_back(glm::vec3(1.0, -1.0,  -1.0));
    squareVertices.push_back(glm::vec3(1.0, 1.0,  -1.0));
    squareVertices.push_back(glm::vec3(-1.0, 1.0,  -1.0));

    //faces.push_back(Face(FRONT,blockInfo.front));
    //faces.push_back(Face(BACK,blockInfo.back));
    //faces.push_back(Face(TOP, blockInfo.top));
    //faces.push_back(Face(BOTTOM, blockInfo.bottom));
    //faces.push_back(Face(LEFT,blockInfo.left));
    //faces.push_back(Face(RIGHT,blockInfo.right));


    squareColors.push_back(glm::vec4(.0, 1., 0.0,1.0));
    squareColors.push_back(glm::vec4(.0, 1., 0.0,1.0));
    squareColors.push_back(glm::vec4(.0, 1., 0.0,1.0));
    squareColors.push_back(glm::vec4(.0, 1., 0.0,1.0));
    squareColors.push_back(glm::vec4(.0, 0., 1.0,1.0));
    squareColors.push_back(glm::vec4(.0, 0., 1.0,1.0));
    squareColors.push_back(glm::vec4(.0, 0., 1.0,1.0));
    squareColors.push_back(glm::vec4(.0, 0., 1.0,1.0));

    textureCor.push_back(glm::vec2(0,0));
    textureCor.push_back(glm::vec2(1,0));
    textureCor.push_back(glm::vec2(1,1));
    textureCor.push_back(glm::vec2(0,1));
    textureCor.push_back(glm::vec2(0,0));
    textureCor.push_back(glm::vec2(1,0));
    textureCor.push_back(glm::vec2(1,1));
    textureCor.push_back(glm::vec2(0,1));
   // calculatePoints();
}

Block::Block(BlockInfo blockInfo,glm::vec3 pos,int offset)
:Block(blockInfo)
{
    this->pos =pos;
    //calculatePoints(offset);
}

Block::~Block() {

}

void Block::addFace(DIR face) {
    switch (face) {
        case LEFT:
            faces.push_back(Face(LEFT,blockInfo.left));
            break;
        case FRONT:
            faces.push_back(Face(FRONT,blockInfo.front));
            break;
        case BACK:
            faces.push_back(Face(BACK,blockInfo.back));
            break;
        case TOP:
            faces.push_back(Face(TOP, blockInfo.top));
            break;
        case BOTTOM:
            faces.push_back(Face(BOTTOM, blockInfo.bottom));
            break;
        case RIGHT:
            faces.push_back(Face(RIGHT,blockInfo.right));
            break;
    }
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

void Block::clearFaces() {
    faces.clear();
}

std::vector<float> Block::getAllVertices(int offset) {
    std::vector<float> ret;
    indices.clear();
    int indCounter = offset;

    //std::cout << "Pos x " << pos.x << std::endl;

    for (auto & face : faces) {
        int texCounter = 0;
        for(auto & indice : face.indices){
            ret.push_back(squareVertices.at(indice).x+pos.x);
            ret.push_back(squareVertices.at(indice).y+pos.y);
            ret.push_back(squareVertices.at(indice).z+pos.z);

            ret.push_back(0.5f);
            ret.push_back(0.5f);
            ret.push_back(0.5f);


            ret.push_back(face.texturePos[texCounter]);
            ret.push_back(face.texturePos[texCounter+1]);
            ret.push_back(face.textureId);

            indices.push_back(indCounter);
            indCounter++;

            texCounter+=2;
        }
    }
    return ret;
}

std::vector<float> Block::getAllVertexesV() {
    std::vector<float> ret;
    for (int j = 0; j < vertices.size(); ++j) {
        ret.push_back(vertices.at(j).x);
        ret.push_back(vertices.at(j).y);
        ret.push_back(vertices.at(j).z);
    }
    return ret;
}

std::vector<unsigned int> Block::getAllIndicesV(int offset) {
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
