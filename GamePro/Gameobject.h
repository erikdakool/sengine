//
// Created by erik on 22.12.18.
//

#ifndef GAMEPRO_GAMEOBJECT_H
#define GAMEPRO_GAMEOBJECT_H

#include <memory>
#include <list>
#include <string>

#include "Components/Transform.h"
#include "Components/RenderCom.h"
#include "Manager.h"

enum ObjectTag{
    TagGameobject = 0,
    TagPlayer = 1,
    TagEnemey = 2,
    TagLayer = 3,
    TagObject = 4
};

class App;
class Gameobject {
public:
    Gameobject(unsigned int id, bool active,RenderData& renderData);
    ~Gameobject();
    virtual void init();
    virtual void update(float deltaT);
    virtual void destroy();

    bool isActive() const {
        return active;
    }
    void setActive(bool active) {
        Gameobject::active = active;
    }

    bool setId(unsigned int id){
        Gameobject::id = id;
    }

    unsigned int getId() const{
        return id;
    }

    template<typename T>
    T getComponent();

    RenderData& getRenderData() const;

    Transform* trasform()const { return this->transform.get();}

private:
    //Gameobject info
    unsigned int id;
    std::string name;
    bool active;
    ObjectTag tag = TagGameobject;

    //Controllers
    RenderData& renderData;

    //transform
    std::unique_ptr<Transform> transform;

    //Components
    std::list<std::shared_ptr<Component>> components;
};


#endif //GAMEPRO_GAMEOBJECT_H