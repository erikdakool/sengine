//
// Created by erik on 23.12.18.
//

#ifndef GAMEPRO_MANAGER_H
#define GAMEPRO_MANAGER_H

//Manager
#include "WindowController.h"
//InputData

//AssetData
#include "AssetController.h"

//Manager
#include "ObjectController.h"
#include "CollisionController.h"
#include "ObjectLoader.h"
#include "Components/InputController.h"
#include "GraphicsController.h"
#include "ObjectFactory.h"

struct Manager {
    Manager(sf::RenderWindow& window)
            :windowController(window){}
    //Render controllers
    WindowController windowController;
    //Asset controller
    AssetController assetController;
    //ObjectControllers
    ObjectLoader objectStreamer;
    ObjectController objectController;
    CollisionController collisionController;
    InputController inputController;
    GraphicsController graphicsController;
    ObjectFactory objectFactory;
};

typedef std::shared_ptr<Manager> Data;

#endif //GAMEPRO_MANAGER_H
