#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "test.pb.h"

#include <string>
int main()
{
    GOOGLE_PROTOBUF_VERSION;
    test::Test test1;
    test1.set_id(123123123);
    test1.set_text("hello world");

    std::string  string;
    test1.SerializeToString(&string);
    std::cout << string << std::endl;

    test::Test test2;
    test2.ParseFromString(string);
    std::cout << test2.id() << std::endl;
    std::cout << test2.text() << std::endl;

    google::protobuf::ShutdownProtobufLibrary();

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("codeFirstModel.png"))
        return EXIT_FAILURE;

    sf::Sprite sprite(texture);
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("OpenSans-Regular.ttf"))
        return EXIT_FAILURE;

    sf::Text text("Hello SFML", font, 50);
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
        // Draw the sprite
        window.draw(sprite);
        // Draw the string
        window.draw(text);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}