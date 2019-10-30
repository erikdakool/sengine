//
// Created by erik on 23.10.2019.
//

#include "Object.h"

Object::Object(GameDataRef data)
:_data(data)
{

}

Object::~Object() = default;

unsigned int Object::getId() const {
    return id;
}

