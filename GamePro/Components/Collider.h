//
// Created by erik on 27.12.18.
//

#ifndef GAMEPRO_COLLIDER_H
#define GAMEPRO_COLLIDER_H

#include <SFML/Graphics.hpp>

#include "Component.h"

class Gameobject;
class Collider : public Component{
    Collider(Gameobject& gameobject);
    ~Collider();

    void init();
    void update(float deltaT);
};

#endif //GAMEPRO_COLLIDER_H
