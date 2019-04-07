//
// Created by  on 30.03.19.
//

#ifndef GAMEPRO_AUDIOCOM_H
#define GAMEPRO_AUDIOCOM_H

#include <SFML/Audio.hpp>

#include "Component.h"

class AudioCom : public Component, public sf::Sound {
public:
    AudioCom(Gameobject& gameobject);
    AudioCom(Gameobject& gameobject, Json::Value input);
    ~AudioCom();

    void init();
    void update(float deltaT);
    Json::Value getJson();
    void setValuesJson(Json::Value input);

private:

};

#endif //
