//
// Created by erik on 27.12.18.
//

#include "ObjectController.h"
#include "Gameobject.h"
#include "Components/PlayerController.h"
#include "Components/Physics.h"

ObjectController::ObjectController() {

}

ObjectController::~ObjectController() {

}

void ObjectController::update(float deltaT) {
    for(auto i = objects.begin(); i != objects.end();i++){
        if(i->get()->isActive()){
            i->get()->update(deltaT);
        } else{
            i=objects.erase(i);
        }
    }
}

Json::Value ObjectController::getJson() {
    Json::Value gameobjects;
    for (auto i = objects.begin(); i != objects.end(); i++) {
        gameobjects.append(i->get()->getJson());
    }
    return gameobjects;
}

void ObjectController::spawnPlayer() {
    auto object = std::make_shared<Gameobject>(11, true,*manager);

    auto playerController = std::make_shared<PlayerController>(*object.get());
    object.get()->AddComponent(playerController);

    auto render = object.get()->getComponentP<RenderCom*>();
    render->setColor(sf::Color::Red);

    auto physics = std::make_shared<Physics>(*object.get());
    object.get()->AddComponent(physics);

    object.get()->trasform()->setY(0);
    object.get()->trasform()->setX(500);
    objects.push_back(object);
    player = object;
}

void ObjectController::addObject(std::shared_ptr<Gameobject> object) {
    if(object->isActive()){
        objects.push_back(object);
    } else{
        inactiveObjects.push_back(object);
    }
}

void ObjectController::clearInactive() {
    for(auto i = inactiveObjects.begin(); i != inactiveObjects.end(); i++){
        i->get()->destroy();
    }
    inactiveObjects.clear();
}