//
// Created by erik on 26.10.2019.
//

#include "CollisionManager.h"

CollisionManager::CollisionManager() {
    rp3d::WorldSettings settings = rp3d::WorldSettings();
    settings.defaultVelocitySolverNbIterations = 20;
    settings.isSleepingEnabled = false;

    world = std::make_unique<rp3d::CollisionWorld>(settings);
}

CollisionManager::~CollisionManager() {

}

rp3d::CollisionBody* CollisionManager::addCollider(rp3d::Transform& transform) {
    rp3d::CollisionBody* body = world->createCollisionBody(transform);
    return body;
}

void CollisionManager::destroyCollision(rp3d::CollisionBody *body) {
    world->destroyCollisionBody(body);
}