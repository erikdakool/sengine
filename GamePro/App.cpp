//
// Created by erik on 22.12.18.
//
#include <iostream>
#include <ctime>

#include "App.h"

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
        auto object = std::make_shared<Gameobject>(i,true,renderData,objectData);
        objectData.objectController.addObject(object);
    }

    for (int i = 5; i <10; ++i) {
        auto object = std::make_shared<Gameobject>(i, false,renderData,objectData);
        objectData.objectController.addObject(object);
    }

    objectData.objectController.clearInactive();

    while(running){
        float deltaT = clock.getElapsedTime().asMilliseconds();
        //std::cout << clock.getElapsedTime().asMilliseconds() << std::endl;
        objectData.objectController.update(deltaT);
        objectData.objectController.draw();
        renderData.windowController.drawToWindow();
        clock.restart();
    }
}