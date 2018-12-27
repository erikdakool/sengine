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
    ~Movement();
    int counter;
};


#endif //GAMEPRO_MOVEMENT_H
