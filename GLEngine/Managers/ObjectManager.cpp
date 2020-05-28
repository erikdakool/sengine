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
    object->setId(objectcount);
    objectcount++;
    objects.push_back(object);
}

void ObjectManager::RemoveObject(uint64_t id){
    pendingRemove.push_back(id);
}

void ObjectManager::UpdateAll(float deltaT) {
    for(auto i = objects.begin(); i != objects.end(); i++){
        if(std::find(pendingRemove.begin(),pendingRemove.end(),i->get()->getId())!=pendingRemove.end()){
            objects.erase(i);
        }else{
            i->get()->update(deltaT);
        }
    }
}