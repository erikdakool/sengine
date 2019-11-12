//
// Created by erik on 12.11.2019.
//

#include "Excavator.h"

Excavator::Excavator(GameDataRef data):
Gameobject(data)
{
    auto renderer = std::make_shared<Renderer>(*this,_data);
    Gameobject::AddComponent(renderer);
}

Excavator::~Excavator() {

}

void Excavator::update(float deltaT) {
    auto rotation = transform().getRotation().y;
    std::cout << glm::radians(rotation) << std::endl;
    if(_data->inputManager.isKeyPressed(GLFW_KEY_U)){
        transform().move(glm::vec3(sin(glm::radians(rotation)),0,cos(glm::radians(rotation))));
    }else if(_data->inputManager.isKeyPressed(GLFW_KEY_J)){
        transform().move(glm::vec3(-sin(glm::radians(rotation)),0,-cos(glm::radians(rotation))));
    }else if(_data->inputManager.isKeyPressed(GLFW_KEY_H)){
        transform().RotateY(5);
    }else if(_data->inputManager.isKeyPressed(GLFW_KEY_K)){
        transform().RotateY(-5);
    }
    Gameobject::update(deltaT);
}