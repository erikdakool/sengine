//
// Created by erik on 27.12.18.
//

#include <iostream>
#include "Movement.h"
#include "../Gameobject.h"
#include "Physics.h"

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
    //getGameobject().trasform()->increaseX(deltaT*speed);
    auto phys = getGameobject().getComponentP<Physics*>();
    phys->addFor(Right,deltaT*speed);
    auto col = getGameobject().getComponentP<Collider*>();
    auto t = getGameobject().getManager().collisionController.collision(*getGameobject().getComponentP<Collider*>());
    if(t){
        getGameobject().trasform()->setX(t->getGameobject().trasform()->getX()+t->getXOff()-col->getWidth());
    }
}

void Movement::moveLeft(float deltaT) {
    //getGameobject().trasform()->decreaseX(deltaT*speed);
    auto phys = getGameobject().getComponentP<Physics*>();
    phys->addFor(Left,deltaT*speed);
    auto t = getGameobject().getManager().collisionController.collision(*getGameobject().getComponentP<Collider*>());
    if(t){
        getGameobject().trasform()->setX(t->getGameobject().trasform()->getX()+t->getXOff()+t->getWidth());
    }
}

void Movement::moveDown(float deltaT) {
    //getGameobject().trasform()->increaseY(deltaT*speed);
    auto phys = getGameobject().getComponentP<Physics*>();
    phys->addFor(Down,deltaT*speed);
    auto col = getGameobject().getComponentP<Collider*>();
    auto t = getGameobject().getManager().collisionController.collision(*getGameobject().getComponentP<Collider*>());
    if(t){
        getGameobject().trasform()->setY(t->getGameobject().trasform()->getY()+t->getYOff()-col->getHeight());
    }
}

void Movement::moveUp(float deltaT) {
    //getGameobject().trasform()->decreaseY(deltaT*speed);
    auto phys = getGameobject().getComponentP<Physics*>();
    phys->addFor(Up,deltaT*speed);
    auto t = getGameobject().getManager().collisionController.collision(*getGameobject().getComponentP<Collider*>());
    if(t){
        getGameobject().trasform()->setY(t->getGameobject().trasform()->getY()+t->getYOff()+t->getHeight());
    }
}