//
// Created by erik on 23.10.2019.
//

#ifndef GLENGINE_GAMEOBJECT_H
#define GLENGINE_GAMEOBJECT_H

#include <list>

#include "../Components/Component.h"
#include "../Managers.h"
#include "../Transform.h"
#include "../Object/Object.h"
class Gameobject : public Object {
public:
    Gameobject(GameDataRef data);
    ~Gameobject();
    Transform& transform();
    void update(float deltaT) override;
    void AddComponent(std::shared_ptr<Component> component);
private:

protected:
    //Gameobject info/data
    bool isChild = false;
    Transform transformcom;

    //Compoents
    std::list<std::shared_ptr<Component>> components;

    //Gameobject family
    std::list<std::shared_ptr<Gameobject>> parent;
    std::list<std::shared_ptr<Gameobject>> children;
};

#endif //GLENGINE_GAMEOBJECT_H
