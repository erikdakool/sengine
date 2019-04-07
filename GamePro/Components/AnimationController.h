//
// Created by erik on 23.03.19.
//

#ifndef GAMEPRO_ANIMATIONCONTROLLER_H
#define GAMEPRO_ANIMATIONCONTROLLER_H

#include <memory>
#include <map>

#include "Component.h"
#include "RenderCom.h"
#include "../DataTypes/Animation.h"

class AnimationController : public Component{
public:
    AnimationController(Gameobject& gameobject);
    AnimationController(Gameobject& gameobject, Json::Value input);
    ~AnimationController();

    void init();
    void update(float deltaT);

    void setAnimation(std::string input);

    Json::Value getJson();
    void setValuesJson(Json::Value input);
private:
    std::map<std::string, std::shared_ptr<Animation>> animations;
    std::shared_ptr<Animation> cAnimation;
    RenderCom* renderCom;
};


#endif //GAMEPRO_ANIMATION_H
