//
// Created by erik on 22.12.18.
//
#include <iostream>
#include <ctime>

#include "App.h"
#include "Components/PlayerController.h"
App::App()
:renderData(*this)
{
    srand(time(NULL));//Restarts so we dont get the same randoms.
}

App::~App() {

}

void App::run() {
    sf::Clock clock;
    sf::Event event;

    //Handle input
    while (this->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)this->close();
    }

    for (int i = 0; i <5; ++i) {
        auto object = std::make_shared<Gameobject>(i, false,renderData,objectData);
        objectData.objectController.addObject(object);
    }

    for (int i = 5; i <10; ++i) {
        auto object = std::make_shared<Gameobject>(i, false,renderData,objectData);
        objectData.objectController.addObject(object);
    }

    auto object = std::make_shared<Gameobject>(11, true,renderData,objectData);
    auto playerController = std::make_shared<PlayerController>(*object.get());
    object.get()->AddComponent(playerController);
    objectData.objectController.addObject(object);

    objectData.objectController.clearInactive();

    while(running){
        //float deltaT = clock.getElapsedTime().asMilliseconds();
        float deltaT = 1.f/60.f;
        //std::cout << clock.getElapsedTime().asMilliseconds() << std::endl;
        objectData.objectController.update(deltaT);
        objectData.objectController.draw();
        renderData.windowController.drawToWindow();
        clock.restart();
    }
}