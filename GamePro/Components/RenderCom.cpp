//
// Created by erik on 23.12.18.
//

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
    auto tex = std::make_shared<sf::Texture>();
    tex->loadFromFile("Data/Textures/Sample_3D.png");
    this->textureRectCon->texture = tex;
    sf::IntRect intRect(0,0,1000,1000);
    this->textureRectCon->intRect = intRect;

    this->setTexture(*this->textureRectCon->texture);
    this->setTextureRect(this->textureRectCon->intRect);
    this->setPosition(0,0);
    this->setScale(1,1);
}

void RenderCom::update(float deltaT) {
    this->setTexture(*this->textureRectCon->texture);
    this->setTextureRect(this->textureRectCon->intRect);
    this->getGameobject().getRenderData().windowController.draw(*this);
}