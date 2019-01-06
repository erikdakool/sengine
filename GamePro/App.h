//
// Created by erik on 22.12.18.
//

#ifndef GAMEPRO_APP_H
#define GAMEPRO_APP_H

#include <memory>
#include <list>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Gameobject.h"
#include "Manager.h"

class App : public sf::RenderWindow{
public:
    App();
    ~App();
    void run();
private:
    bool running = true;
    Manager manager;
};

#endif //GAMEPRO_APP_H
