//
// Created by erik on 01.04.19.
//

#include "Animation.h"

Animation::Animation() {

}

Animation::Animation(Json::Value input, AssetController assetController) {
    this->animationTime = input["animTime"].asFloat();
    this->animationFrame = input["animFrame"].asUInt();

    for(Json::Value& animation: input["animations"]){
        duration.push_back(animation["animTime"].asFloat());
        auto rect = std::make_shared<TextureRect>(animation["animation"],assetController);
        rects.push_back(rect);
    }
}

Animation::~Animation() {

}

Json::Value Animation::getJson(AssetController assetController) {
    Json::Value ret;
    ret["animTime"] = this->animationTime;
    ret["animFrame"] = this->animationFrame;

    Json::Value animArray;
    for (int i = 0; i < rects.size(); ++i) {
        Json::Value anima;
        anima["animation"] = rects.at(i).get()->getJson(assetController);
        anima["animTime"] = duration.at(i);
        animArray.append(anima);
    }
    ret["animations"] = animArray;
    return ret;
}
