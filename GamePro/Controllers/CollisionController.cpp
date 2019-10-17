//
// Created by erik on 27.12.18.
//

#include <iostream>
#include "CollisionController.h"
#include "../Gameobjects/Gameobject.h"

CollisionController::CollisionController() {

}

CollisionController::~CollisionController() {

}

Collider* CollisionController::collision(Collider &collider) {
    for(auto i = colliders.begin(); i != colliders.end();i++) {
        if(i->get()->checkCollision(collider)){
            return i->get();
        }
    }
    return nullptr;
}

void CollisionController::addCollider(std::shared_ptr<Collider> collider) {
    colliders.push_back(collider);
}

void CollisionController::removeCollider() {
    for(auto i = colliders.begin(); i != colliders.end();i++) {
        if(i->get()->isDestroy()){
            i = colliders.erase(i);
            i--;
        }
    }
}

Collider* CollisionController::checkCollision(Collider &collider, Dir dir, float distance) {
    float tx = collider.getXOff();
    float ty = collider.getYOff();
    switch (dir){
        case Right:
            collider.setXOff(collider.getXOff()+distance);
            break;
        case Left:
            collider.setXOff(collider.getXOff()-distance);
            break;
        case Up:
            collider.setYOff(collider.getYOff()-distance);
            break;
        case Down:
            collider.setYOff(collider.getYOff()+distance);
            break;
    }
    auto ret = collision(collider);
    collider.setYOff(ty);
    collider.setXOff(tx);
    return ret;
}