//
// Created by erik on 23.10.2019.
//

#include "Gameobject.h"

Gameobject::Gameobject(GameDataRef data)
:Object(data)
{
    transformcom = new Transform(*this);
}

Gameobject::~Gameobject() {

}

void Gameobject::update(float deltaT) {
    for(auto & component : components){
        component->update(deltaT);
    }
    for(auto & child : children){
        child->update(deltaT);
    }
}

Transform &Gameobject::transform() {
    return *this->transformcom;
}

void Gameobject::AddComponent(std::shared_ptr<Component> component) {
    components.push_back(component);
}

void Gameobject::AddChild(std::shared_ptr<Gameobject> gameobject) {
    children.push_back(gameobject);
}

std::vector<std::shared_ptr<Gameobject>> Gameobject::getChildren() {
    return children;
}

uint32_t Gameobject::getId() const {
    return id;
}

void Gameobject::setId(uint32_t id) {
    Gameobject::id = id;
}
