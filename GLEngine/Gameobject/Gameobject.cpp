//
// Created by erik on 23.10.2019.
//

#include "Gameobject.h"

Gameobject::Gameobject(GameDataRef data)
:Object(data)
{

}

Gameobject::~Gameobject() {

}

void Gameobject::update(float deltaT) {
    for(auto & component : components){
        component->update(deltaT);
    }
}

Transform &Gameobject::transform() {
    return this->transformcom;
}

void Gameobject::AddComponent(std::shared_ptr<Component> component) {
    components.push_back(component);
}