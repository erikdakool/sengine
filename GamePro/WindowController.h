//
// Created by erik on 23.12.18.
//

#ifndef GAMEPRO_WINDOWCONTROLLER_H
#define GAMEPRO_WINDOWCONTROLLER_H

#include <SFML/Graphics.hpp>

class WindowController {
public:
    WindowController(sf::RenderWindow& window);
    ~WindowController();

    void draw(sf::Sprite& sprite);
    void drawToWindow();

private:
    sf::RenderTexture gameOut;
    sf::RenderTexture interfaceOut;
    sf::RenderWindow& window;
    sf::VideoMode vm;
};


#endif //GAMEPRO_WINDOWCONTROLLER_H
