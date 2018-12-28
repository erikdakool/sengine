//
// Created by erik on 22.12.18.
//

#include "Gameobject.h"
#include "Components/RenderCom.h"
#include "Components/Movement.h"

Gameobject::Gameobject(unsigned int id, bool active,RenderData& renderData,ObjectData& objectData)
:renderData(renderData),objectData(objectData)
{
    this->id = id;
    this->active = active;
    auto renderCom = std::make_shared<RenderCom>(*this);
    components.push_back(std::move(renderCom));
    auto move = std::make_shared<Movement>(*this);
    //components.push_back(std::move(move));
    auto collider = std::make_shared<Collider>(*this);
    components.push_back(collider);
    objectData.collisionController.addCollider(collider);
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
    auto com = getComponentP<RenderCom *>();
    auto movement = getComponentP<Movement *>();
}

void Gameobject::destroy() {
    for(auto i = components.begin(); i != components.end();i++){
        i->get()->setDestroy(true);
    }
    objectData.collisionController.removeCollider();
}

template <typename T>
T Gameobject::getComponentP() {
    for(auto i = components.begin(); i != components.end();i++){
        auto com = dynamic_cast<T>(i->get());
        if(com){
            return com;
        }
    }
    return nullptr;
}


RenderData& Gameobject::getRenderData() const {
    return renderData;
}