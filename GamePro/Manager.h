//
// Created by erik on 23.12.18.
//

#ifndef GAMEPRO_MANAGER_H
#define GAMEPRO_MANAGER_H

#include "WindowController.h"

struct RenderData{
    RenderData(sf::RenderWindow& window)
    :windowController(window){}
    WindowController windowController;
};

struct InputData{

};

struct AssetData{

};


#endif //GAMEPRO_MANAGER_H
