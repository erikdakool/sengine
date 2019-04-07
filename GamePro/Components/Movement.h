//
// Created by erik on 27.12.18.
//

#ifndef GAMEPRO_MOVEMENT_H
#define GAMEPRO_MOVEMENT_H


#include "Component.h"

class Gameobject;
class Movement : public Component {
public:
    Movement(Gameobject& gameobject);
    Movement(Gameobject& gameobject, Json::Value input);

    ~Movement();

    void init();
    void update(float deltaT);
    Json::Value getJson();
    void setValuesJson(Json::Value input);
    void moveLeft(float deltaT);
    void moveRight(float deltaT);
    void moveUp(float deltaT);
    void moveDown(float deltaT);

private:
    float speed = 100.0f;
};


#endif //GAMEPRO_MOVEMENT_H
