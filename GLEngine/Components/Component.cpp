//
// Created by erik on 23.10.2019.
//

#include "Component.h"

#include <utility>

Component::Component(Gameobject& gameobject, GameDataRef data):
gameobject(gameobject),Object(std::move(data))
{

}

Component::~Component() {

}

