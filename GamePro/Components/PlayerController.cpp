//
// Created by erik on 28.12.18.
//

#include <SFML/System.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

#include "PlayerController.h"
#include "../Gameobject.h"
#include "Movement.h"

PlayerController::PlayerController(Gameobject &gameobject)
:Component(gameobject)
{
    Movement* movement = gameobject.getComponentP<Movement *>();
    this->movement =  movement;
}

PlayerController::~PlayerController() {

}

void PlayerController::init() {

}

void PlayerController::update(float deltaT) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        movement->moveUp(deltaT);
        std::cout << getGameobject().trasform()->getY() << std::endl;
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