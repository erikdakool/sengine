//
// Created by erik on 25.10.2019.
//

#ifndef GLENGINE_COLLIDER_H
#define GLENGINE_COLLIDER_H


#include "Component.h"
#include <reactphysics3d/reactphysics3d.h>

class Collider : public Component {
public:
    Collider(Gameobject& gameobject,GameDataRef data);
    ~Collider();
    void update(float deltaT) override;

private:
    void updateCollisionTransform(rp3d::Transform& transform);
    rp3d::CollisionBody* body;
};


#endif //GLENGINE_COLLIDER_H
