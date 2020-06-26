//
// Created by erik on 25.10.2019.
//

#ifndef GLENGINE_COLLIDER_H
#define GLENGINE_COLLIDER_H


#include "Component.h"

class Collider : public Component {
public:
    Collider(Gameobject& gameobject,GameDataRef data);
    ~Collider();
    void update(float deltaT) override;


};


#endif //GLENGINE_COLLIDER_H
