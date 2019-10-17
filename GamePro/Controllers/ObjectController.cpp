//
// Created by erik on 27.12.18.
//

#include "ObjectController.h"
#include "../Gameobjects/Gameobject.h"
#include "../Components/PlayerController.h"
#include "../Components/Physics.h"
#include "../Components/AudioCom.h"

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

void ObjectController::initAll() {
    for(auto i = objects.begin(); i != objects.end();i++){
        if(i->get()->isActive()){
            i->get()->init();
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

void ObjectController::addPlayer(std::shared_ptr<Gameobject> gameobject) {
    this->player = gameobject;
}

void ObjectController::spawnPlayer() {
    auto object = std::make_shared<Gameobject>(11, true,*manager);

    auto playerController = std::make_shared<PlayerController>(*object.get());
    object.get()->addComponent(playerController);

    auto render = std::make_shared<RenderCom>(*object.get());
    render->setColor(sf::Color::Red);
    object.get()->addComponent(render);

    auto collider = std::make_shared<Collider>(*object.get());
    object.get()->addComponent(collider);
    manager->collisionController.addCollider(collider);

    auto physics = std::make_shared<Physics>(*object.get());
    object.get()->addComponent(physics);

    auto sound = std::make_shared<AudioCom>(*object.get());
    object.get()->addComponent(sound);

    auto mov = std::make_shared<Movement>(*object.get());
    object.get()->addComponent(mov);

    object.get()->trasform()->setY(0);
    object.get()->trasform()->setX(500);
    object.get()->setName("player");
    object.get()->setTag(TagPlayer);

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