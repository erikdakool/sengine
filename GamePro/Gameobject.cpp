//
// Created by erik on 22.12.18.
//

#include "Gameobject.h"
#include "Components/RenderCom.h"
#include "Components/Movement.h"

Gameobject::Gameobject(unsigned int id, bool active,Manager& manager)
:manager(manager)
{
    this->transform = std::make_unique<Transform>();
    this->id = id;
    this->active = active;
    auto renderCom = std::make_shared<RenderCom>(*this);
    components.push_back(std::move(renderCom));
    auto move = std::make_shared<Movement>(*this);
    components.push_back(std::move(move));
    auto collider = std::make_shared<Collider>(*this);
    components.push_back(collider);
    manager.collisionController.addCollider(collider);
}

Gameobject::~Gameobject() {

}

void Gameobject::init() {

}

void Gameobject::update(float deltaT) {
    for(auto i = components.begin(); i != components.end();i++){
        if (i->get()->isActive()){
            i->get()->update(deltaT);
        }
    }
}

void Gameobject::destroy() {
    for(auto i = components.begin(); i != components.end();i++){
        i->get()->setDestroy(true);
    }
    manager.collisionController.removeCollider();
}

void Gameobject::AddComponent(std::shared_ptr<Component> component) {
    components.push_back(component);
}

Manager &Gameobject::getManager() const {
    return manager;
}

Json::Value Gameobject::getJson() {
    Json::Value gameobject;
    gameobject["id"] = this->id;
    gameobject["name"] = this->name;
    gameobject["activity"] = this->active;
    gameobject["tag"] = this->tag;

    Json::Value cArray;
    for(auto i = components.begin(); i != components.end();i++){
        cArray.append(i->get()->getJson());
    }
    gameobject["components"] = cArray;
    gameobject["transform"] = trasform()->getJson();
    return gameobject;
}