//
// Created by erik on 27.12.18.
//

#include "CollisionController.h"

CollisionController::CollisionController() {

}

CollisionController::~CollisionController() {

}

Collider* CollisionController::collision(Collider &collider) {
    for(auto i = colliders.begin(); i != colliders.end();i++) {
        if(i->get()->checkCollision(collider))
            return i->get();
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