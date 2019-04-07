//
// Created by erik on 28.12.18.
//

#ifndef GAMEPRO_PLAYERCONTROLLER_H
#define GAMEPRO_PLAYERCONTROLLER_H

#include <memory>
#include <bits/shared_ptr.h>
#include "Component.h"
#include "Movement.h"

class PlayerController : public Component {
public:
    PlayerController(Gameobject& gameobject);
    PlayerController(Gameobject& gameobject, Json::Value input);

    ~PlayerController();

    void init();
    void update(float deltaT);
    Json::Value getJson();
    void setValuesJson(Json::Value input);

private:
    Movement* movement;
    std::shared_ptr<Gameobject> flame;
    float rot = 0;
};


#endif //GAMEPRO_PLAYERCONTROLLER_H
