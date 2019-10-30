//
// Created by erik on 23.10.2019.
//

#ifndef GLENGINE_COMPONENT_H
#define GLENGINE_COMPONENT_H

#include "../Object/Object.h"
#include "../Managers.h"

class Gameobject;
class Component : public Object{
public:
    Component(Gameobject& gameobject,GameDataRef data);
    ~Component();

private:

protected:
    Gameobject& gameobject;
};

#endif //GLENGINE_COMPONENT_H
