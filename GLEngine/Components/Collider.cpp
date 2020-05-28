//
// Created by erik on 25.10.2019.
//

#include "Collider.h"
#include "../Gameobject/Gameobject.h"
Collider::Collider(Gameobject &gameobject, GameDataRef data):
Component(gameobject,data)
{

}

Collider::~Collider() {
}

void Collider::update(float deltaT) {

}
