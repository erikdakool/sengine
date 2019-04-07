//
// Created by erik on 22.12.18.
//
#include <iostream>
#include <ctime>

#include <SFML/Window/Joystick.hpp>

#include "App.h"
#include "Components/Physics.h"

App::App()
:manager(*this)
{
    manager.objectController.manager = &manager;
    manager.objectStreamer.manager = &manager;
    manager.objectFactory.manager = &manager;
    srand(time(NULL));//Restarts so we dont get the same randoms.
}

App::~App() {

}

void App::run() {
    sf::Clock clock;
    sf::Event event;

    bool load = false;
    if(!load){
        for (int i = 0; i < 14; ++i) {
            for (int j = 0; j < 14; ++j) {
                auto object = std::make_shared<Gameobject>((i*j)+i, true,manager);

                auto collider = std::make_shared<Collider>(*object.get());
                object.get()->addComponent(collider);
                manager.collisionController.addCollider(collider);

                auto phys = std::make_shared<Physics>(*object.get());
                //object.get()->addComponent(phys);

                object.get()->trasform()->setX(i*41);
                object.get()->trasform()->setY(j*41+100);
                manager.objectController.addObject(object);
            }
        }

        manager.objectController.spawnPlayer();
        manager.objectController.clearInactive();
        manager.objectStreamer.writeScene();
    } else{
        manager.objectStreamer.loadScene();
        manager.objectStreamer.writeScene();
    }

    manager.objectController.initAll();


    sf::Joystick::Identification id = sf::Joystick::getIdentification(0);
    manager.windowController.setTitle("Joystick " + id.name.toAnsiString());

    std::cout << sf::Joystick::getButtonCount(0) << std::endl;
    std::cout << sf::Joystick::getIdentification(0).name.toAnsiString() << std::endl;

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