//
// Created by erik on 23.10.2019.
//

#ifndef GLENGINE_PHYSICS_H
#define GLENGINE_PHYSICS_H

#include "Component.h"

#include <glm/glm.hpp>

class Physics : public Component{
public:
    Physics(Gameobject& gameobject, GameDataRef data);
    ~Physics();
    void update(float deltaT) override ;
    void push(glm::vec3 v);
    void addVel(glm::vec3 v);

private:
    glm::vec3 force = glm::vec3(0,0,0);
    glm::vec3 imp = glm::vec3(0,0,0);
    glm::vec3 cacc = glm::vec3(0,0,0);
    glm::vec3 lacc = glm::vec3(0,0,0);
    glm::vec3 vel = glm::vec3(0,0,0);
    float mass = 10;
    float dragCo = .004f;
};

#endif //GLENGINE_PHYSICS_H
