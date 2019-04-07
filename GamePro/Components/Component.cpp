//
// Created by erik on 22.12.18.
//

#include "Component.h"

Component::Component(Gameobject &gameobject):
gameobject(gameobject)
{

}

Component::Component(Gameobject &gameobject, Json::Value input):
gameobject(gameobject)
{

}

Component::~Component() {

}

void Component::init() {

}

void Component::update(float deltaT) {

}

Json::Value Component::getJson() {

}

Json::Value Component::getCJson() {
    Json::Value ret;
    ret["id"] = this->id;
    ret["active"] = this->active;
    return ret;
}

void Component::setValuesJson(Json::Value input) {
    this-> id = input["id"].asUInt();
    this->active = input["active"].asBool();
}

Gameobject &Component::getGameobject() const {
    return gameobject;
}

bool Component::isDestroy() const {
    return destroy;
}

void Component::setDestroy(bool destroy) {
    Component::destroy = destroy;
}

bool Component::isActive() const {
    return active;
}

void Component::setActive(bool active) {
    Component::active = active;
}

unsigned int Component::getId() const {
    return id;
}

void Component::setId(unsigned int id) {
    Component::id = id;
}
