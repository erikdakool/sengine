#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "Cube.h"

int main()
{
    double rotate_x = 0;
    bool rotate_xClick =false;
    double rotate_y = 0;
    bool rotate_yClick = false;
    double rotate_z = 0;
    bool rotate_zClick = false;

    std::vector<Cube> cubes;
    cubes.push_back(Cube(.4,.4,.4));
    cubes.push_back(Cube(.2,.2,.2));
    cubes.push_back(Cube(.3,.3,.3));
    cubes[0].Translate(Vector3D(0,-.4,0));
    cubes[1].Translate(Vector3D(-.1,0,0));
    cubes[2].Translate(Vector3D(0,.4,.4));
    //cubes[0].RotateY(45*3.14/180);
    //cubes[0].RotateZ(45*3.14/180);
    //cubes[0].RotateX(45*3.14/180);

    // create the window
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    sf::Window window(sf::VideoMode(1200, 1200), "OpenGL", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    // activate the window
    window.setActive(true);

    // load resources, initialize the OpenGL states, ...

    // run the main loop

    glViewport(0,0, 1200, 1200);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                if(!rotate_xClick){
                    rotate_x +=2;
                    rotate_xClick = true;
                }
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                if(!rotate_xClick){
                    rotate_x -=2;
                    rotate_xClick = true;
                }
            }else{
                rotate_xClick = false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                if(!rotate_yClick){
                    rotate_y +=2;
                    rotate_yClick = true;
                }
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                if(!rotate_yClick){
                    rotate_y -=2;
                    rotate_yClick = true;
                }
            }else{
                rotate_yClick = false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                if(!rotate_zClick){
                    rotate_z +=2;
                    rotate_zClick = true;
                }
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                if(!rotate_zClick){
                    rotate_z -=2;
                    rotate_zClick = true;
                }
            }else{
                rotate_zClick = false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                rotate_x = 0;
                rotate_y = 0;
                rotate_z = 0;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                for(auto& cube : cubes){
                    cube.Scale(Vector3D(.9,.9,.9));
                }
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
                for(auto& cube : cubes){
                    cube.Scale(Vector3D(1.1,1.1,1.1));
                }
            }
        }
        glRotatef(rotate_x,1.0,0.0,0.0);
        glRotatef(rotate_y,0.0,1.0,0.0);
        glRotatef(rotate_z,0.0,0.0,1.0);
        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        for(auto& cube : cubes){
            cube.draw();
        }

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;
}