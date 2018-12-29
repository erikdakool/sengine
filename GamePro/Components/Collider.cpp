//
// Created by erik on 27.12.18.
//

#include "Collider.h"
#include "../Gameobject.h"

#include <iostream>

Collider::Collider(Gameobject &gameobject)
:Component(gameobject)
{

}

Collider::~Collider() {

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

    if(((collider.getGameobject().trasform()->getX()+collider.xOff+collider.getWidth())<= getGameobject().trasform()->getX()+this->xOff))
        return false;
    else if((getGameobject().trasform()->getX()+this->xOff+this->width) <= collider.getGameobject().trasform()->getX()+collider.xOff)
        return false;
    else if((collider.getGameobject().trasform()->getY()+collider.yOff+collider.getHeight()) <= getGameobject().trasform()->getY()+this->yOff)
        return false;
    else if((getGameobject().trasform()->getY()+this->yOff+this->height) <= collider.getGameobject().trasform()->getY()+collider.yOff)
        return false;
    else return true;
}

float Collider::getWidth() const {
    return width;
}

float Collider::getHeight() const {
    return height;
}

float Collider::getXOff() const {
    return xOff;
}

float Collider::getYOff() const {
    return yOff;
}

void Collider::setXOff(float xOff) {
    Collider::xOff = xOff;
}

void Collider::setYOff(float yOff) {
    Collider::yOff = yOff;
}
