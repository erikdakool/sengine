//
// Created by erikdesk on 5/29/20.
//

#ifndef GLENGINE_FACE_H
#define GLENGINE_FACE_H

#endif //GLENGINE_FACE_H

#include <glm/glm.hpp>

enum DIR{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    BACK,
    FRONT
};

struct Face{
    Face();
    Face(DIR dir){
        switch (dir) {
            case FRONT:
                points[0] = glm::vec3(-1,-1,0);
                points[1] = glm::vec3(-1,1,0);
                points[2] = glm::vec3(1,1,0);

                points[4] = glm::vec3(-1,-1,0);
                points[3] = glm::vec3(1,1,0);
                points[5] = glm::vec3(1,-1,0);
                break;
            default:
                break;
        }
    };

    glm::vec3 points[6];
};