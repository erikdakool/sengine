//
// Created by erik on 22.12.18.
//
#include <iostream>
#include <ctime>

#include "App.h"
#include "Components/Physics.h"

App::App()
:renderData(*this)
{
    objectData.objectController.objectData = &objectData;
    objectData.objectController.renderData = &renderData;
    srand(time(NULL));//Restarts so we dont get the same randoms.
}

App::~App() {

}

void App::run() {
    sf::Clock clock;
    sf::Event event;

    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 40; ++j) {
            auto object = std::make_shared<Gameobject>((i*j)+i, true,renderData,objectData);
            auto phys = std::make_shared<Physics>(*object.get());
            object.get()->AddComponent(phys);
            object.get()->trasform()->setX(i*41);
            object.get()->trasform()->setY(j*41+100);
            objectData.objectController.addObject(object);
        }
    }

    objectData.objectController.spawnPlayer();
    objectData.objectController.clearInactive();
    while(running){
        //Handle input
        renderData.windowController.updateCamera(*objectData.objectController.player);
        while (this->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)this->close();
        }

        //float deltaT = clock.getElapsedTime().asMilliseconds();
        float deltaT = 1.f/60.f;
        std::cout << clock.getElapsedTime().asMilliseconds() << std::endl;
        objectData.objectController.update(deltaT);
        renderData.windowController.drawToWindow();
        clock.restart();
    }
}