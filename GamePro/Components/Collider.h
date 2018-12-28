//
// Created by erik on 27.12.18.
//

#ifndef GAMEPRO_COLLIDER_H
#define GAMEPRO_COLLIDER_H

#include <SFML/Graphics.hpp>

#include "Component.h"

class Gameobject;
class Collider : public Component{
public:
    Collider(Gameobject& gameobject);
    ~Collider();

    void init();
    void update(float deltaT);
    bool checkCollision(Collider& collider);

    float getX() const;

    float getY() const;

    float getWidth() const;

    float getHeight() const;

private:
    float x = 0, y = 0;
    float width = 0, height = 0;
    bool collider = true;
    bool trigger = false;
    unsigned int eventId;
};

#endif //GAMEPRO_COLLIDER_H