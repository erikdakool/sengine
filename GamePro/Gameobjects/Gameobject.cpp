//
// Created by erik on 22.12.18.
//

#include "Gameobject.h"
#include "../Components/RenderCom.h"
#include "../Components/Movement.h"

Gameobject::Gameobject(unsigned int id, bool active,Manager& manager)
:manager(manager)
{
    this->transform = std::make_shared<Transform>(*this);
    components.push_back(transform);

    this->id = id;
    this->active = active;
}

Gameobject::Gameobject(Manager &manager)
:manager(manager)
{

}

Gameobject::~Gameobject() {

}

void Gameobject::init() {
    for(auto i = components.begin(); i != components.end();i++){
        if (i->get()->isActive()){
            i->get()->init();
        }
    }
    for(auto i = children.begin(); i!=children.end(); i++){
        i->get()->init();
    }
}

void Gameobject::update(float deltaT) {
    for(auto i = components.begin(); i != components.end();i++){
        if (i->get()->isActive()){
            i->get()->update(deltaT);
        }
    }
    for(auto i = children.begin(); i!=children.end(); i++){
        i->get()->update(deltaT);
    }
}

void Gameobject::destroy() {
    for(auto i = components.begin(); i != components.end();i++){
        i->get()->setDestroy(true);
    }
    if(getComponentP<Collider*>()){
        manager.collisionController.removeCollider();
    }

    for(auto i = children.begin(); i != children.end(); i++){
        i->get()->destroy();
    }
}

void Gameobject::addComponent(std::shared_ptr<Component> component) {
    components.push_back(component);
}

Manager &Gameobject::getManager() const {
    return manager;
}

Json::Value Gameobject::getJson() {
    Json::Value gameobject;
    gameobject["id"] = this->id;
    gameobject["name"] = this->name;
    gameobject["active"] = this->active;
    gameobject["tag"] = this->tag;

    Json::Value cArray;
    for(auto i = components.begin(); i != components.end();i++){
        cArray.append(i->get()->getJson());
    }
    gameobject["components"] = cArray;
    return gameobject;
}

void Gameobject::loadComponent(Json::Value &value) {

}

const std::shared_ptr<Gameobject> &Gameobject::getParent() const {
    return parent;
}

const std::list<std::shared_ptr<Gameobject>> &Gameobject::getChildren() const {
    return children;
}

void Gameobject::setParent(std::shared_ptr<Gameobject> parent) {
    Gameobject::parent = parent;
}

void Gameobject::addChildren(std::shared_ptr<Gameobject> child) {
    children.push_back(child);
}

const std::string &Gameobject::getName() const {
    return name;
}

ObjectTag Gameobject::getTag() const {
    return tag;
}

void Gameobject::setName(const std::string &name) {
    Gameobject::name = name;
}

void Gameobject::setTag(ObjectTag tag) {
    Gameobject::tag = tag;
}

