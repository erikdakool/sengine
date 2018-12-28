//
// Created by erik on 27.12.18.
//

#include <iostream>
#include "Movement.h"
#include "../Gameobject.h"

Movement::Movement(Gameobject &gameobject)
:Component(gameobject)
{
}

Movement::~Movement() {

}

void Movement::init() {

}

void Movement::update(float deltaT) {

}

void Movement::moveRight(float deltaT) {
    getGameobject().trasform()->increaseX(deltaT*speed);
}

void Movement::moveLeft(float deltaT) {
    getGameobject().trasform()->decreaseX(deltaT*speed);
}

void Movement::moveDown(float deltaT) {
    getGameobject().trasform()->increaseY(deltaT*speed);
}

void Movement::moveUp(float deltaT) {
    getGameobject().trasform()->decreaseY(deltaT*speed);
}