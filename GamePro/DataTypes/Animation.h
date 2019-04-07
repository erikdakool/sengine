//
// Created by erik on 01.04.19.
//

#ifndef GAMEPRO_ANIMATION_H
#define GAMEPRO_ANIMATION_H

#include <memory>

#include "TextureRect.h"

class Animation {
public:
    Animation();
    Animation(Json::Value input, AssetController assetController);
    ~Animation();

    Json::Value getJson(AssetController assetController);

    std::vector<std::shared_ptr<TextureRect>> rects;
    std::vector<float> duration;
    float animationTime = 0;
    unsigned int animationFrame = 0;
};


#endif //GAMEPRO_ANIMATION_H
