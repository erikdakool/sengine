//
// Created by erik on 22.12.18.
//

#include "Component.h"

Component::Component(Gameobject &gameobject):
gameobject(gameobject)
{

}

Component::~Component() {

}

void Component::init() {

}

void Component::update(float deltaT) {

}

Gameobject &Component::getGameobject() const {
    return gameobject;
}

bool Component::isActive() const {
    return active;
}
