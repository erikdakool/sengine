//
// Created by erik on 27.12.18.
//

#include "Collider.h"
#include "../Gameobject.h"

#include <iostream>

Collider::Collider(Gameobject &gameobject)
:Component(gameobject)
{
    std::cout << "collider made" << std::endl;
}

Collider::~Collider() {
    std::cout << "Collider deleted" << std::endl;
}

void Collider::init() {

}

void Collider::update(float deltaT) {

}

bool Collider::checkCollision(Collider& collider) {
    if (!this->collider)
        return false;

    //returns false if objects checks with itself
    if (this->getGameobject().getId() == collider.getGameobject().getId())
        return false;

    if(((collider.getX()+collider.getWidth())<= this->x))
        return false;
    else if((this->x+this->width) <= collider.getX())
        return false;
    else if((collider.getY()+collider.getHeight()) <= this->y)
        return false;
    else if((this->y+this->height) <= collider.getY())
        return false;
    else return true;
}

float Collider::getX() const {
    return x;
}

float Collider::getY() const {
    return y;
}

float Collider::getWidth() const {
    return width;
}

float Collider::getHeight() const {
    return height;
}
