//
// Created by erik on 23.12.18.
//

#ifndef GAMEPRO_MANAGER_H
#define GAMEPRO_MANAGER_H

//Manager
#include "Controllers/WindowController.h"
//InputData

//AssetData
#include "Controllers/AssetController.h"

//Manager
#include "Controllers/ObjectController.h"
#include "Controllers/CollisionController.h"
#include "Controllers/ObjectLoader.h"
#include "Components/InputController.h"
#include "Controllers/GraphicsController.h"
#include "Controllers/ObjectFactory.h"

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
