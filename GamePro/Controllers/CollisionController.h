//
// Created by erik on 27.12.18.
//

#ifndef GAMEPRO_COLLISIONCONTROLLER_H
#define GAMEPRO_COLLISIONCONTROLLER_H

#include <memory>
#include <list>

#include "../Components/Collider.h"

class CollisionController {
public:
    CollisionController();
    ~CollisionController();

    Collider* collision(Collider& collider);
    void addCollider(std::shared_ptr<Collider> collider);
    void removeCollider();
    Collider* checkCollision(Collider& collider, Dir dir, float distance);
private:
    std::list<std::shared_ptr<Collider>> colliders;
};


#endif //GAMEPRO_COLLISIONCONTROLLER_H
