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

Movement::Movement(Gameobject &gameobject, Json::Value input)
:Component(gameobject)
{
    Movement::setValuesJson(input);
}

Movement::~Movement() {

}

void Movement::init() {

}

void Movement::update(float deltaT) {

}

Json::Value Movement::getJson() {
    Json::Value ret;
    ret = Component::getCJson();
    ret["name"] = "movement";
    ret["speed"] = this->speed;
    return ret;
}

void Movement::setValuesJson(Json::Value input) {
    Component::setValuesJson(input);
    this->speed = input["speed"].asFloat();
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