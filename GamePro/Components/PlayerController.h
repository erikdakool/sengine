//
// Created by erik on 28.12.18.
//

#ifndef GAMEPRO_PLAYERCONTROLLER_H
#define GAMEPRO_PLAYERCONTROLLER_H


#include "Component.h"
#include "Movement.h"

class PlayerController : public Component {
public:
    PlayerController(Gameobject& gameobject);
    ~PlayerController();

    void init();
    void update(float deltaT);

private:
    Movement* movement;
};


#endif //GAMEPRO_PLAYERCONTROLLER_H
