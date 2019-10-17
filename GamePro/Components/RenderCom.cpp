//
// Created by erik on 23.12.18.
//

#include <iostream>
#include "RenderCom.h"

#include "../Gameobjects/Gameobject.h"

RenderCom::RenderCom(Gameobject &gameobject)
:Component(gameobject)
{

}

RenderCom::RenderCom(Gameobject &gameobject, Json::Value input)
        :Component(gameobject)
{
    RenderCom::setValuesJson(input);
}

RenderCom::~RenderCom() {

}

void RenderCom::init() {
    getGameobject().getManager().assetController.loadTexture("tex","Data/Textures/Sample_3D.png");
    auto tex = getGameobject().getManager().assetController.getTexture("tex");
    auto tRect = std::make_shared<TextureRect>(tex,0,0,40,40);
    this->textureRectCon = tRect;

    this->setTexture(*this->textureRectCon->texture);
    this->setTextureRect(*this->textureRectCon->intRect);
    this->setPosition(getGameobject().trasform()->getX(),getGameobject().trasform()->getY());
    this->setScale(1,1);
    this->setOrigin((float)textureRectCon->intRect->width/2,(float)textureRectCon->intRect->height/2);
    this->setColor(color);
}

void RenderCom::update(float deltaT) {
    draw();
}

void RenderCom::draw() {
    onscreen = getGameobject().getManager().windowController.onScreen(*this);
    if(!onscreen)
        return;
    this->setTexture(*this->textureRectCon->texture);
    this->setTextureRect(*this->textureRectCon->intRect);
    this->setRotation(getGameobject().trasform()->getRotation());
    setPosition(getGameobject().trasform()->getX(),getGameobject().trasform()->getY());
    getGameobject().getManager().windowController.draw(*this);
}

Json::Value RenderCom::getJson() {
    Json::Value ret = Component::getCJson();
    ret["name"] = "rendercom";
    return ret;}

void RenderCom::setValuesJson(Json::Value input) {
    Component::setValuesJson(input);
}