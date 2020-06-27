//
// Created by erikdesk on 5/29/20.
//

#ifndef GLENGINE_FACE_H
#define GLENGINE_FACE_H

#include <glm/glm.hpp>

enum DIR{
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    BACK,
    FRONT
};

struct Face{
    Face(DIR dir, int textureId){
        switch (dir) {
            case FRONT:
                indices = {0,1,2,2,3,0};
                texturePos={0,0,1,0,1,1,1,1,0,1,0,0};
                break;
            case BACK:
                indices = {4,7,6,6,5,4};
                texturePos={0,0,0,1,1,1,1,1,1,0,0,0};
                break;
            case LEFT:
                indices = {4,0,3,3,7,4};
                texturePos={0,0,1,0,1,1,1,1,0,1,0,0};
                break;
            case RIGHT:
                indices = {1,5,6,6,2,1};
                texturePos={0,0,1,0,1,1,1,1,0,1,0,0};
                break;
            case TOP:
                indices = {3,2,6,6,7,3};
                texturePos={0,0,1,0,1,1,1,1,0,1,0,0};
                break;
            case BOTTOM:
                indices ={1,0,4,4,5,1};
                texturePos={0,0,1,0,1,1,1,1,0,1,0,0};
                break;
            default:
                break;
        }
        this->textureId = textureId;
    };

    std::vector<unsigned int> indices;
    std::vector<float> texturePos;
    float textureId;
};

#endif //GLENGINE_FACE_H
