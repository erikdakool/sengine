//
// Created by  on 30.03.19.
//

#include "AudioCom.h"

#include "../Gameobject.h"

AudioCom::AudioCom(Gameobject& gameobject)
:Component(gameobject)
{
    init();
}

AudioCom::AudioCom(Gameobject &gameobject, Json::Value input)
:Component(gameobject)
{
    setValuesJson(input);
}

AudioCom::~AudioCom(){

}

void AudioCom::init() {
    getGameobject().getManager().assetController.loadSoundbuffer("sb","Data/Audio/phaserUp2.wav");
    auto sb = getGameobject().getManager().assetController.getSoundbuffer("sb");
    this->setBuffer(*sb.get());
    this->play();
    this->setLoop(true);
}

void AudioCom::update(float deltaT) {

}

Json::Value AudioCom::getJson() {
    Json::Value ret;
    ret = Component::getCJson();
    ret["name"] = "audioCom";
    return ret;
}

void AudioCom::setValuesJson(Json::Value input) {
    Component::setValuesJson(input);
}