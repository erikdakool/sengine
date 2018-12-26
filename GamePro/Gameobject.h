//
// Created by erik on 22.12.18.
//

#ifndef GAMEPRO_GAMEOBJECT_H
#define GAMEPRO_GAMEOBJECT_H

#include <memory>

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
    RenderData& getRenderData() const;

private:
    std::unique_ptr<Transform> transform;
    RenderCom* renderCom;
    RenderData& renderData;
    unsigned int id;
    bool active;
    ObjectTag tag = TagGameobject;
};


#endif //GAMEPRO_GAMEOBJECT_H