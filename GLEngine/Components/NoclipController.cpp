//
// Created by erikdesk on 5/28/20.
//

#include "NoclipController.h"
#include "../Gameobject/Gameobject.h"

NoclipController::NoclipController(Gameobject &gameobject, GameDataRef data):
Component(gameobject,data)
{
    transform = &gameobject.transform();
}

NoclipController::~NoclipController() {

}

void NoclipController::update(float deltaT) {
    if(_data->inputManager.isKeyPressed(GLFW_KEY_UP)){
        transform->move(glm::vec3(0,0,1));
    }
    if(_data->inputManager.isKeyPressed(GLFW_KEY_DOWN)){
        transform->move(glm::vec3(0,0,-1));
    }
    if(_data->inputManager.isKeyPressed(GLFW_KEY_RIGHT)){
        transform->move(glm::vec3(1,0,0));
    }
    if(_data->inputManager.isKeyPressed(GLFW_KEY_LEFT)){
        transform->move(glm::vec3(-1,0,0));
    }
}