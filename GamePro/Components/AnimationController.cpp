//
// Created by erik on 23.03.19.
//

#include "AnimationController.h"

#include "../Gameobjects/Gameobject.h"

AnimationController::AnimationController(Gameobject& gameobject)
:Component(gameobject)
{
    getGameobject().getManager().assetController.loadTexture("flame","Data/Textures/engineFlame.png");
    auto tex = getGameobject().getManager().assetController.getTexture("flame");
    auto anim = std::make_shared<Animation>();
    this->cAnimation = anim;
    for (int i = 0; i < 8; ++i) {
        auto rect = std::make_shared<TextureRect>(tex,0+32*i,0,32,32);
        anim.get()->rects.push_back(rect);
        anim.get()->duration.push_back(.2f);
    }
}

AnimationController::AnimationController(Gameobject &gameobject, Json::Value input)
:Component(gameobject)
{
    setValuesJson(input);

}

AnimationController::~AnimationController() {

}


void AnimationController::init() {
    renderCom = gameobject.getComponentP<RenderCom*>();
    renderCom->textureRectCon  = cAnimation.get()->rects.at(0);
}

void AnimationController::update(float deltaT) {
    cAnimation->animationTime+=deltaT;
    if(cAnimation->animationTime > cAnimation->duration.at(cAnimation->animationFrame)){
        cAnimation->animationFrame++;
        if(cAnimation->animationFrame >= cAnimation->rects.size()){
            cAnimation->animationFrame = 0;
        }
        cAnimation->animationTime = 0;
        renderCom->textureRectCon = cAnimation->rects.at(cAnimation->animationFrame);
    }
}

void AnimationController::setAnimation(std::string input) {
    if(animations.find(input) == animations.end()){
        cAnimation = animations.at(input);
    }
}


Json::Value AnimationController::getJson() {
    Json::Value ret = Component::getCJson();
    ret["name"] = "animationController";
    ret["cAnimation"] = cAnimation.get()->getJson(gameobject.getManager().assetController);

    std::map<std::string, std::shared_ptr<Animation>>::iterator it = animations.begin();
    auto itl = animations.begin();
    Json::Value animArray;
    while (it != animations.end())
    {
        Json::Value animation;
        animation["animation"] = it->second->getJson(gameobject.getManager().assetController);
        animation["name"] = it->first;
        animArray.append(animation);
        it++;
    }
    ret["animations"] = animArray;
    return ret;
}

void AnimationController::setValuesJson(Json::Value input) {
    Component::setValuesJson(input);
    for(Json::Value& animation: input["animations"]){
        auto anim = std::make_shared<Animation>(animation["animation"],gameobject.getManager().assetController);
        animations.at(animation["name"].asString()) = anim;
    }
    auto anim = std::make_shared<Animation>(input["cAnimation"],gameobject.getManager().assetController);
    this->cAnimation = anim;
}