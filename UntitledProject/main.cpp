#include <iostream>

#include <SFML/Graphics.hpp>
#include <tensorflow/c/c_api.h>

int main() {
    sf::RenderWindow window(sf::VideoMode(800,800),"OpenGL");
    window.setVerticalSyncEnabled(true);
    window.setActive(true);
    sf::Texture texture;
    texture.loadFromFile("/none.png");
    sf::Sprite sprite(texture);
    sprite.setTextureRect(sf::IntRect(800,800,800,800));
    sprite.setColor(sf::Color::Blue);

    std::cout << TF_Version() << std::endl;

    while (window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return EXIT_SUCCESS;
}