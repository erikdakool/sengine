//
// Created by erik on 29.12.18.
//

#ifndef GAMEPRO_PHYSICS_H
#define GAMEPRO_PHYSICS_H

#include "Component.h"
#include "Collider.h"

class Physics : public Component{
public:
    Physics(Gameobject& gameobject);
    ~Physics();

    void init();
    void update(float deltaT);
    Json::Value getJson();
    void setValuesJson(Json::Value input);

    void addFor(Dir dir, float value);
    void addVel(Dir dir, float value);
private:
    float xFor = 0, yFor = 0;
    float xImp = 0, yImp = 0;
    float cxAcc = 0, cyAcc = 0;
    float lyAcc = 0, lxAcc = 0;
    float xVel = 0, yVel = 0;
    float mass = 10;
    float dragCo = .004f;
    Collider* col;
};


#endif //GAMEPRO_PHYSICS_H
