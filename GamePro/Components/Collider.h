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
    explicit Collider(Gameobject& gameobject);
    ~Collider();

    void init();
    void update(float deltaT);
    bool checkCollision(Collider& collider);

    float getXOff() const;

    void setXOff(float xOff);

    void setYOff(float yOff);

    float getYOff() const;

    float getWidth() const;

    float getHeight() const;

private:
    float xOff = 0;
    float yOff = 0;
    float width = 40, height = 40;
    bool collider = true;
    bool trigger = false;
    unsigned int eventId;
};

#endif //GAMEPRO_COLLIDER_H