//
// Created by erik on 26.10.2019.
//

#ifndef GLENGINE_COLLISIONMANAGER_H
#define GLENGINE_COLLISIONMANAGER_H

#include <reactphysics3d/reactphysics3d.h>

class CollisionManager {
public:
    CollisionManager();
    ~CollisionManager();

    rp3d::CollisionBody* addCollider(rp3d::Transform& transform);
    void destroyCollision(rp3d::CollisionBody* body);
private:
    std::unique_ptr<rp3d::CollisionWorld> world;
};


#endif //GLENGINE_COLLISIONMANAGER_H
