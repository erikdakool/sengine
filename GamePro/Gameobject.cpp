//
// Created by erik on 22.12.18.
//

#include "Gameobject.h"

Gameobject::Gameobject(unsigned int id, bool active,RenderData& renderData)
:renderData(renderData)
{
    this->id = id;
    this->active = active;
    renderCom = new RenderCom(*this);
}

Gameobject::~Gameobject() {

}

void Gameobject::init() {

}

void Gameobject::update(float deltaT) {
    renderCom->update(deltaT);
}

void Gameobject::destroy() {

}

RenderData& Gameobject::getRenderData() const {
    return renderData;
}