//
// Created by erik on 25.10.2019.
//

#include "Collider.h"
#include "../Gameobject/Gameobject.h"
Collider::Collider(Gameobject &gameobject, GameDataRef data):
Component(gameobject,data)
{
    rp3d::Vector3 initPosition = gameobject.transform().getRPVPosition();
    rp3d::Quaternion initOrientation = rp3d::Quaternion::identity();
    rp3d::Transform transform = rp3d::Transform(initPosition,initOrientation);

    body = data->collisionManager.addCollider(transform);
}

Collider::~Collider() {
    _data->collisionManager.destroyCollision(body);
}

void Collider::update(float deltaT) {

}

void Collider::updateCollisionTransform(rp3d::Transform &transform) {
    body->setTransform(transform);
}