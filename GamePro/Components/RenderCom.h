//
// Created by erik on 23.12.18.
//

#ifndef GAMEPRO_RENDERCOM_H
#define GAMEPRO_RENDERCOM_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "Component.h"

struct TextureRect{
    sf::IntRect intRect;
    std::shared_ptr<sf::Texture> texture;
};

class RenderCom : public Component, public sf::Sprite {
public:
    RenderCom(Gameobject& gameobject);
    ~RenderCom();

    void init();
    void update(float deltaT);

private:
    std::shared_ptr<TextureRect> textureRectCon;
    sf::Color color = sf::Color(255,255,255);
};


#endif //GAMEPRO_RENDERCOM_H
