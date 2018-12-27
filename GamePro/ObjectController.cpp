//
// Created by erik on 27.12.18.
//

#include "ObjectController.h"
#include "Gameobject.h"

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

void ObjectController::draw() {

}

void ObjectController::addObject(std::shared_ptr<Gameobject> object) {
    if(object->isActive()){
        objects.push_back(object);
    } else{
        inactiveObjects.push_back(object);
    }
}
