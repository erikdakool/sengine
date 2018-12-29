//
// Created by erik on 23.12.18.
//

#include "WindowController.h"
#include "Gameobject.h"
WindowController::WindowController(sf::RenderWindow& window)
:window(window)
{
    sf::Vector2i screenDimension(800,600);
    vm.width = screenDimension.x;
    vm.height = screenDimension.y;
    this->window.create(vm, "Hello world!",sf::Style::Close | sf::Style::Titlebar);
    this->window.setVerticalSyncEnabled(true);
    this->window.setFramerateLimit(60);
    gameOut.create(screenDimension.x,screenDimension.y);
}

WindowController::~WindowController() {

}

void WindowController::draw(sf::Sprite &sprite) {
    sprite.setPosition(sprite.getPosition().x-camera.x,sprite.getPosition().y-camera.y);
    gameOut.draw(sprite);
}

void WindowController::drawToWindow() {
    window.setActive(true);
    window.clear();

    this->gameOut.display();
    sf::Sprite spriteGame(this->gameOut.getTexture());
    window.draw(spriteGame);

    this->interfaceOut.display();
    sf::Sprite spriteInterface(this->interfaceOut.getTexture());
    window.draw(spriteInterface);

    window.display();
    this->gameOut.clear(sf::Color::Transparent);
    this->interfaceOut.clear(sf::Color::Transparent);
}

void WindowController::updateCamera(Gameobject& gameobject) {
    camera.x = gameobject.trasform()->getX() - camera.width/2;
    camera.y = gameobject.trasform()->getY() - camera.height/2;
}
