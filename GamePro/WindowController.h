//
// Created by erik on 23.12.18.
//

#ifndef GAMEPRO_WINDOWCONTROLLER_H
#define GAMEPRO_WINDOWCONTROLLER_H

#include <SFML/Graphics.hpp>

struct Camera{
    float x;
    float y;
    float width = 800;
    float height = 600;
};

class Gameobject;
class WindowController {
public:
    explicit WindowController(sf::RenderWindow& window);
    ~WindowController();

    void draw(sf::Sprite& sprite);
    void drawToWindow();
    void updateCamera(Gameobject& gameobject);
    bool onScreen(sf::Sprite& sprite);
private:
    sf::RenderTexture gameOut;
    sf::RenderTexture interfaceOut;
    sf::RenderWindow& window;
    sf::VideoMode vm;
    Camera camera;
};


#endif //GAMEPRO_WINDOWCONTROLLER_H
