//
// Created by erik on 22.12.18.
//

#include "Gameobject.h"
#include "Components/RenderCom.h"
#include "Components/Movement.h"

Gameobject::Gameobject(unsigned int id, bool active,RenderData& renderData)
:renderData(renderData)
{
    this->id = id;
    this->active = active;
    auto renderCom = std::make_shared<RenderCom>(*this);
    components.push_back(std::move(renderCom));
    auto move = std::make_shared<Movement>(*this);
    move->counter = 100;
    //components.push_back(std::move(move));
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
    RenderCom* com = getComponent<RenderCom*>();
    Movement* movement = nullptr;
    movement = getComponent<Movement*>();
}

void Gameobject::destroy() {

}

template <typename T>
T Gameobject::getComponent() {
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