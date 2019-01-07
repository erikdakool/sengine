//
// Created by erik on 22.12.18.
//
#include <iostream>
#include <ctime>

#include "App.h"
#include "Components/Physics.h"

App::App()
:manager(*this)
{
    manager.objectController.manager = &manager;
    manager.objectStreamer.manager = &manager;
    srand(time(NULL));//Restarts so we dont get the same randoms.
}

App::~App() {

}

void App::run() {
    sf::Clock clock;
    sf::Event event;

    for (int i = 0; i < 140; ++i) {
        for (int j = 0; j < 140; ++j) {
            auto object = std::make_shared<Gameobject>((i*j)+i, true,manager);
            auto phys = std::make_shared<Physics>(*object.get());
            //object.get()->AddComponent(phys);
            object.get()->trasform()->setX(i*41);
            object.get()->trasform()->setY(j*41+100);
            manager.objectController.addObject(object);
        }
    }

    manager.objectController.spawnPlayer();
    manager.objectController.clearInactive();

    manager.objectStreamer.writeScene();

    while(running){
        //Handle input
        manager.windowController.updateCamera(*manager.objectController.player);
        while (this->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)this->close();
        }

        //float deltaT = clock.getElapsedTime().asMilliseconds();
        float deltaT = 1.f/60.f;
        //std::cout << clock.getElapsedTime().asMilliseconds() << std::endl;
        manager.objectController.update(deltaT*3);
        manager.windowController.drawToWindow();
        clock.restart();
    }
}