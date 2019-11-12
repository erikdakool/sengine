//
// Created by erik on 12.11.2019.
//

#ifndef GLENGINE_EXCAVATOR_H
#define GLENGINE_EXCAVATOR_H

#include "../Components/Component.h"
#include "../Components/Renderer.h"
#include "Gameobject.h"
class Excavator : public Gameobject{
public:
    Excavator(GameDataRef data);
    ~Excavator();
    void update(float deltaT) override;

private:
    std::shared_ptr<Gameobject> tracks;
    std::shared_ptr<Gameobject> cabin;
    std::shared_ptr<Gameobject> arm1;
    std::shared_ptr<Gameobject> arm2;
    std::shared_ptr<Gameobject> boom;
};


#endif //GLENGINE_EXCAVATOR_H
