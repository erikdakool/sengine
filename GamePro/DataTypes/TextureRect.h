//
// Created by erik on 23.03.19.
//

#ifndef GAMEPRO_TEXTURERECT_H
#define GAMEPRO_TEXTURERECT_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <json/json.h>
#include "../Controllers/AssetController.h"

class TextureRect {
public:
    TextureRect(std::shared_ptr<sf::Texture>  tex);
    TextureRect(std::shared_ptr<sf::Texture>  tex, int x, int y, int width, int height);
    TextureRect(Json::Value input, AssetController assetController);
    ~TextureRect();

    Json::Value getJson(AssetController assetController);

    std::shared_ptr<sf::IntRect> intRect;
    std::shared_ptr<sf::Texture> texture;
};


#endif //GAMEPRO_TEXTURERECT_H
