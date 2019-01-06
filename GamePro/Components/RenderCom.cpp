//
// Created by erik on 23.12.18.
//

#include <iostream>
#include "RenderCom.h"

#include "../Gameobject.h"

RenderCom::RenderCom(Gameobject &gameobject)
:Component(gameobject)
{
    init();
}

RenderCom::~RenderCom() {

}

void RenderCom::init() {
    auto tRect = std::make_shared<TextureRect>();
    this->textureRectCon = tRect;

    getGameobject().getManager().assetController.loadTexture("tex","Data/Textures/Sample_3D.png");
    tRect->texture=getGameobject().getManager().assetController.getTexture("tex");

    sf::IntRect intRect(0,0,40,40);
    this->textureRectCon->intRect = intRect;

    this->setTexture(*this->textureRectCon->texture);
    this->setTextureRect(this->textureRectCon->intRect);
    this->setPosition(getGameobject().trasform()->getX(),getGameobject().trasform()->getY());
    this->setScale(1,1);
    this->setOrigin((float)intRect.width/2,(float)intRect.height/2);
    this->setColor(color);
}

void RenderCom::update(float deltaT) {
    onscreen = getGameobject().getManager().windowController.onScreen(*this);
    if(!onscreen)
        return;
    this->setTexture(*this->textureRectCon->texture);
    this->setTextureRect(this->textureRectCon->intRect);
    this->setRotation(getGameobject().trasform()->getRotation());
    setPosition(getGameobject().trasform()->getX(),getGameobject().trasform()->getY());
    getGameobject().getManager().windowController.draw(*this);
}