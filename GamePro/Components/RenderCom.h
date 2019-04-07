//
// Created by erik on 23.12.18.
//

#ifndef GAMEPRO_RENDERCOM_H
#define GAMEPRO_RENDERCOM_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "Component.h"
#include "../DataTypes/TextureRect.h"

class RenderCom : public Component, public sf::Sprite {
    friend class AnimationController;
public:
    RenderCom(Gameobject& gameobject);
    RenderCom(Gameobject& gameobject, Json::Value input);

    ~RenderCom();

    void init();
    void update(float deltaT);
    void draw();
    Json::Value getJson();
    void setValuesJson(Json::Value input);

private:
    std::shared_ptr<TextureRect> textureRectCon;
    sf::Color color = sf::Color(255,255,255);
    bool onscreen;
};

#endif //GAMEPRO_RENDERCOM_H
