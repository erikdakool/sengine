//
// Created by erik on 28.12.18.
//

#ifndef GAMEPRO_PLAYERCONTROLLER_H
#define GAMEPRO_PLAYERCONTROLLER_H

#include <memory>
#include <bits/shared_ptr.h>
#include "Component.h"
#include "Movement.h"
#include "Collider.h"
#include "RenderCom.h"
#include "Physics.h"
#include "AudioCom.h"

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
    RenderCom* renderCom;
    Collider* collider;
    Movement* movement;
    Physics* physics;
    AudioCom* audioCom;
};


#endif //GAMEPRO_PLAYERCONTROLLER_H
