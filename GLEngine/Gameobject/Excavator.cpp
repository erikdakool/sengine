//
// Created by erik on 12.11.2019.
//

#include "Excavator.h"

Excavator::Excavator(GameDataRef data):
Gameobject(data)
{
    auto renderer = std::make_shared<Renderer>(*this,_data,"tracks","Data/Excavator/tracks.obj","track","Data/tracktex.bmp");
    Gameobject::AddComponent(renderer);

    this->cabin = std::make_shared<Gameobject>(_data);
    auto rend = std::make_shared<Renderer>(*cabin,_data,"cabin","Data/Excavator/cabin.obj","grey","Data/grey.bmp");
    cabin.get()->AddComponent(rend);
    cabin.get()->transform().move(glm::vec3(0,3,0));

    this->arm1 = std::make_shared<Gameobject>(_data);
    auto arm1rend = std::make_shared<Renderer>(*arm1,_data,"arm1","Data/Excavator/arm1.obj","red","Data/red.bmp");
    arm1.get()->AddComponent(arm1rend);
    arm1.get()->transform().move(glm::vec3(-3,5,5));

    this->arm2 = std::make_shared<Gameobject>(_data);
    auto arm2rend = std::make_shared<Renderer>(*arm2,_data,"arm2","Data/Excavator/arm2.obj","grey","Data/grey.bmp");
    arm2.get()->AddComponent(arm2rend);
    arm2.get()->transform().move(glm::vec3(-3,5,15));

    this->broom = std::make_shared<Gameobject>(_data);
    auto broomrend = std::make_shared<Renderer>(*broom,_data,"broom","Data/Excavator/broom.obj","red","Data/red.bmp");
    broom.get()->AddComponent(broomrend);
    broom.get()->transform().move(glm::vec3(-3,4,25));

    arm2.get()->AddChild(broom);
    arm1.get()->AddChild(arm2);
    cabin.get()->AddChild(arm1);
    AddChild(cabin);
}

Excavator::~Excavator() {

}

void Excavator::update(float deltaT) {
    auto rotation = transform().getRotation().y;
    if(_data->inputManager.isKeyPressed(GLFW_KEY_U)){
        transform().move(glm::vec3(sin(glm::radians(rotation)),0,cos(glm::radians(rotation))));
    }else if(_data->inputManager.isKeyPressed(GLFW_KEY_J)){
        transform().move(glm::vec3(-sin(glm::radians(rotation)),0,-cos(glm::radians(rotation))));
    }else if(_data->inputManager.isKeyPressed(GLFW_KEY_H)){
        transform().RotateY(5);
        cabin.get()->transform().RotateY(5);
        arm1.get()->transform().RotateY(5);
        arm1.get()->transform().RotateAroundPointY(cabin.get()->transform().getPosition(),5);
        arm2.get()->transform().RotateY(5);
        arm2.get()->transform().RotateAroundPointY(cabin.get()->transform().getPosition(),5);
        broom.get()->transform().RotateY(5);
        broom.get()->transform().RotateAroundPointY(cabin.get()->transform().getPosition(),5);
    }else if(_data->inputManager.isKeyPressed(GLFW_KEY_K)){
        transform().RotateY(-5);
        cabin.get()->transform().RotateY(-5);
        arm1.get()->transform().RotateY(-5);
        arm1.get()->transform().RotateAroundPointY(cabin.get()->transform().getPosition(),-5);
        arm2.get()->transform().RotateY(-5);
        arm2.get()->transform().RotateAroundPointY(cabin.get()->transform().getPosition(),-5);
        broom.get()->transform().RotateY(-5);
        broom.get()->transform().RotateAroundPointY(cabin.get()->transform().getPosition(),-5);
    }else if(_data->inputManager.isKeyPressed(GLFW_KEY_Y)){
        cabin.get()->transform().RotateY(5);
        arm1.get()->transform().RotateAroundPointY(cabin.get()->transform().getPosition(),5);
        arm1.get()->transform().RotateY(5);
        arm2.get()->transform().RotateY(5);
        arm2.get()->transform().RotateAroundPointY(cabin.get()->transform().getPosition(),5);
        broom.get()->transform().RotateY(5);
        broom.get()->transform().RotateAroundPointY(cabin.get()->transform().getPosition(),5);
    }else if(_data->inputManager.isKeyPressed(GLFW_KEY_I)){
        cabin.get()->transform().RotateY(-5);
        arm1.get()->transform().RotateY(-5);
        arm1.get()->transform().RotateAroundPointY(cabin.get()->transform().getPosition(),-5);
        arm2.get()->transform().RotateY(-5);
        arm2.get()->transform().RotateAroundPointY(cabin.get()->transform().getPosition(),-5);
        broom.get()->transform().RotateY(-5);
        broom.get()->transform().RotateAroundPointY(cabin.get()->transform().getPosition(),-5);
    }else if(_data->inputManager.isKeyPressed(GLFW_KEY_O)){
        arm1.get()->transform().RotateX(-5);
        auto pointx = arm2.get()->transform().RotateAroundPointX(arm1.get()->transform().getPosition(),-5*cosf(glm::radians(arm2.get()->transform().getRotation().y)));
        auto pointz = arm2.get()->transform().RotateAroundPointZ(arm1.get()->transform().getPosition(),5*sinf(glm::radians(arm2.get()->transform().getRotation().y)));
        broom.get()->transform().move(-pointx);
        broom.get()->transform().move(-pointz);
    }else if(_data->inputManager.isKeyPressed(GLFW_KEY_L)){
        arm1.get()->transform().RotateX(5);
        auto pointx = arm2.get()->transform().RotateAroundPointX(arm1.get()->transform().getPosition(),5*cosf(glm::radians(arm2.get()->transform().getRotation().y)));
        auto pointz = arm2.get()->transform().RotateAroundPointZ(arm1.get()->transform().getPosition(),5*-sinf(glm::radians(arm2.get()->transform().getRotation().y)));
        broom.get()->transform().move(-pointx);
        broom.get()->transform().move(-pointz);
    }else if(_data->inputManager.isKeyPressed(GLFW_KEY_7)){
        arm2.get()->transform().RotateX(-5);
        broom.get()->transform().RotateAroundPointX(arm2.get()->transform().getPosition(),-5*cosf(glm::radians(broom.get()->transform().getRotation().y)));
        broom.get()->transform().RotateAroundPointZ(arm2.get()->transform().getPosition(),5*sinf(glm::radians(broom.get()->transform().getRotation().y)));
    }else if(_data->inputManager.isKeyPressed(GLFW_KEY_8)){
        arm2.get()->transform().RotateX(5);
        broom.get()->transform().RotateAroundPointX(arm2.get()->transform().getPosition(),5*cosf(glm::radians(broom.get()->transform().getRotation().y)));
        broom.get()->transform().RotateAroundPointZ(arm2.get()->transform().getPosition(),5*-sinf(glm::radians(broom.get()->transform().getRotation().y)));
    }else if(_data->inputManager.isKeyPressed(GLFW_KEY_9)){
        broom.get()->transform().RotateX(5);
    }else if(_data->inputManager.isKeyPressed(GLFW_KEY_0)){
        broom.get()->transform().RotateX(-5);
    }
    Gameobject::update(deltaT);
}