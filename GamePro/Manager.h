//
// Created by erik on 23.12.18.
//

#ifndef GAMEPRO_MANAGER_H
#define GAMEPRO_MANAGER_H

//RenderData
#include "WindowController.h"
//InputData

//AssetData

//ObjectData
#include "ObjectController.h"
#include "CollisionController.h"


struct RenderData{
    RenderData(sf::RenderWindow& window)
    :windowController(window){}
    WindowController windowController;
};

struct InputData{

};

struct AssetData{

};

struct ObjectData{
    ObjectController objectController;
    CollisionController collisionController;
};


#endif //GAMEPRO_MANAGER_H
