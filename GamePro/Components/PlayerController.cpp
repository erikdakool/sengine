//
// Created by erik on 28.12.18.
//

#include <SFML/System.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <cmath>

#include "PlayerController.h"
#include "../Gameobject.h"
#include "Movement.h"
#include "AudioCom.h"
#include "Physics.h"
#include "AnimationController.h"

PlayerController::PlayerController(Gameobject &gameobject)
:Component(gameobject)
{
    flame = std::make_shared<Gameobject>(15,true,gameobject.getManager());
    auto anim = std::make_shared<AnimationController>(*flame.get());
    flame.get()->addComponent(anim);

    flame.get()->trasform()->setX(gameobject.trasform()->getX());
    flame.get()->trasform()->setY(gameobject.trasform()->getY());
    gameobject.getManager().objectController.addObject(flame);
    gameobject.addChildren(flame);
}

PlayerController::PlayerController(Gameobject &gameobject, Json::Value input)
        :Component(gameobject)
{
    PlayerController::setValuesJson(input);
}

PlayerController::~PlayerController() {

}

void PlayerController::init() {
    Movement* movement = gameobject.getComponentP<Movement *>();
    this->movement =  movement;
}

void PlayerController::update(float deltaT) {
    if(sf::Joystick::isConnected(0)){
        if(sf::Joystick::getAxisPosition(0,sf::Joystick::X) >= 30 || sf::Joystick::getAxisPosition(0,sf::Joystick::X) <= -30){
            float x;
            x = sf::Joystick::getAxisPosition(0,sf::Joystick::X)/100 * deltaT;
            movement->moveRight(x);
        }
        if(sf::Joystick::getAxisPosition(0,sf::Joystick::Y) >= 1 || sf::Joystick::getAxisPosition(0,sf::Joystick::Y) <= -1){
            float y;
            y = sf::Joystick::getAxisPosition(0,sf::Joystick::Y)/100 * deltaT;
            movement->moveDown(y);
        }
/*        if(sf::Joystick::isButtonPressed(0,7)){
            auto sound = getGameobject().getComponentP<AudioCom*>();
            if(sound->getStatus()==sf::SoundSource::Status::Stopped){
                sound->play();
                sound->setPitch(sound->getPitch()+.1);
            }
        }*/

    } else{
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        movement->moveUp(deltaT);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            movement->moveRight(deltaT);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            movement->moveLeft(deltaT);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            movement->moveDown(deltaT);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
            getGameobject().trasform()->rotateD(1);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
            getGameobject().trasform()->rotateD(-1);
        }
    }

    auto phys = getGameobject().getComponentP<Physics*>();
    float speedX = phys->getXVel();
    float speedY = phys->getYVel();
    float totalSpeed = sqrt((speedX*speedX) + (speedY*speedY));

    auto sound = getGameobject().getComponentP<AudioCom*>();
    sound->setPitch(totalSpeed/5);

    float tan = std::atan2((speedY),speedX);
    tan = tan * 180/3.1415;

    float x = 32*std::cos(tan);
    float y = 32*std::sin(tan);

    //flame.get()->trasform()->setX(getGameobject().trasform()->getX()+x);
    //flame.get()->trasform()->setY(getGameobject().trasform()->getY()+y);
    //flame.get()->trasform()->setRotation(tan);
}

Json::Value PlayerController::getJson() {
    Json::Value ret = Component::getCJson();
    ret["name"] = "playercontroller";
    return ret;}

void PlayerController::setValuesJson(Json::Value input) {
    Component::setValuesJson(input);
}