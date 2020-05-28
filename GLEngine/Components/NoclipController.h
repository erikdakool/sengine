//
// Created by erikdesk on 5/28/20.
//

#ifndef GLENGINE_NOCLIPCONTROLLER_H
#define GLENGINE_NOCLIPCONTROLLER_H

#include"Component.h"
#include "../Transform.h"

class NoclipController : public Component{
public:
    NoclipController(Gameobject& gameobject,GameDataRef data);
    ~NoclipController();

    void update(float deltaT) override;

private:
    Transform* transform;
};


#endif //GLENGINE_NOCLIPCONTROLLER_H
