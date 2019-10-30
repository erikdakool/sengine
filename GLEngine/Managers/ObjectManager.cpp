//
// Created by erik on 23.10.2019.
//

#include "ObjectManager.h"
#include "../Gameobject/Gameobject.h"
ObjectManager::ObjectManager() {

}

ObjectManager::~ObjectManager() {

}

void ObjectManager::AddObject(std::shared_ptr<Gameobject> object) {
    objects.push_back(object);
}

void ObjectManager::UpdateAll(float deltaT) {
    for(auto & gameobject : objects){
        gameobject.get()->update(deltaT);
    }
}