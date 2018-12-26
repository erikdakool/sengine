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
    const float FPS = 60.0f; //The desired FPS. (The number of updates each second).
    bool redraw = true;      //Do I redraw everything on the screen?

    sf::Clock clock;

    sf::Event event;

    if (clock.getElapsedTime().asSeconds() >= 1.0f / FPS)
        //Wait until 1/60th of a second has passed, then update everything.
    {
        redraw = true; //We're ready to redraw everything
        clock.restart();
    } else //Sleep until next 1/60th of a second comes around
    {
        sf::Time sleepTime = sf::seconds((1.0f / FPS) - clock.getElapsedTime().asSeconds());
        sleep(sleepTime);
    }
    //Handle input
    while (this->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)this->close();
    }

    //Draw stuff if ready
    if (redraw)
    {
        redraw = false;
    }


    for (int i = 0; i <5; ++i) {
        auto object = std::make_shared<Gameobject>(i,true,renderData);
        objects.push_back(object);
    }

    for (int i = 5; i <10; ++i) {
        auto object = std::make_shared<Gameobject>(i, false,renderData);
        objects.push_back(object);
    }

    while(running){
        std::cout << clock.getElapsedTime().asMilliseconds() << std::endl;
        for(auto i = objects.begin(); i != objects.end();i++){
            if(i->get()->isActive()){
                i->get()->update(clock.getElapsedTime().asMilliseconds());
            } else{
                i=objects.erase(i);
            }
        }
        renderData.windowController.drawToWindow();
        clock.restart();
    }
}