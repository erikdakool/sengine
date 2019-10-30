//
// Created by erik on 23.10.2019.
//

#include "Physics.h"
#include "../Gameobject/Gameobject.h"

Physics::Physics(Gameobject &gameobject, GameDataRef data):
Component(gameobject,data){

}

Physics::~Physics() {

}

void Physics::update(float deltaT) {
    auto rFor = glm::vec3(0,0,0);
    force = (cacc*mass*deltaT)-rFor + imp;

    auto posD = vel * deltaT + (0.5f*lacc*(deltaT*deltaT));
    auto acc = force/mass;
    auto avAcc = (lacc + acc)/2.0f;
    vel += avAcc * deltaT;
    lacc = acc;
    gameobject.transform().move(posD);

    imp = imp*0.f;
}

void Physics::push(glm::vec3 v) {
    imp += v;
}

void Physics::addVel(glm::vec3 v) {
    vel += v;
}