#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <math.h>
#include <assert.h>
#include "Cube.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

Matrix<double> getPerspective(double const& fov, double const& ratio, double const& near, double const& far){
    double const frustumDepth = far-near;
    double const oneOverDepth = 1/frustumDepth;
    double const rad = fov*M_PI/180.0;
    double const tanhalvfov = tan(rad /2);

    Matrix<double> matrix = Matrix<double>(4,4);
    matrix[1][1] = tanhalvfov;
    matrix[0][0] = -1 * matrix[1][1] / ratio;
    matrix[2][2] = far * oneOverDepth;
    matrix[3][2] = (-far * near) * oneOverDepth;
    matrix[2][3] = 1;
    matrix[3][3] = 0;
    return matrix;
}

int main()
{
    Camera camera = Camera();
    int width = 800;
    int height = 800;
    float aspectRatio = (float)width/(float)height;
    float near = 0.1;
    float far = 100.0;
    float fov = 90.0;

    camera.perspectiveMatrix = getPerspective(fov,aspectRatio,near,far);


    glm::mat4 matrix = glm::perspective(fov,aspectRatio,near,far);
    for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < 4; ++i) {
            camera.perspectiveMatrix[j][i] = matrix[j][i];
        }
    }
    matrix[1][1];

    //Input initialization
    double rotate_x = 0;
    bool rotate_xClick =false;
    double rotate_y = 0;
    bool rotate_yClick = false;
    double rotate_z = 0;
    bool rotate_zClick = false;


    srand (time(NULL));
    //Primitives initialization
    std::vector<Cube> cubes;
    for (int i = 0; i < 5; ++i) {
        for(int y = 0; y< 5; y ++){
            Cube t = Cube(.2,.2,.2);
            t.transformcom.Move(Vector3D((float)i/2,(float)y/2,-1));
            double zoff = rand()% 10+1;
            t.transformcom.Move(Vector3D(0,0,zoff/10));
            cubes.emplace_back(t);
        }
    }

    //cubes[0].Rotate(Vector3D(.1,.1,.1));
    //cubes.emplace_back(.2,.2,.2);
    //cubes.emplace_back(.3,.3,.3);
    //[0].Translate(Vector3D(0,-.4,0));
    //cubes[1].Translate(Vector3D(-.1,0,0));
    //cubes[2].Translate(Vector3D(0,.4,.4));
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

    sf::Window window(sf::VideoMode(width, height), "OpenGL", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    // activate the window
    window.setActive(true);

    // load resources, initialize the OpenGL states, ...

    // run the main loop

    glViewport(0,0, width, height);

    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
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
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
                if(!rotate_xClick){
                    rotate_x +=2;
                    rotate_xClick = true;
                }
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
                if(!rotate_xClick){
                    rotate_x -=2;
                    rotate_xClick = true;
                }
            }else{
                rotate_xClick = false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)){
                if(!rotate_yClick){
                    rotate_y +=2;
                    rotate_yClick = true;
                }
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)){
                if(!rotate_yClick){
                    rotate_y -=2;
                    rotate_yClick = true;
                }
            }else{
                rotate_yClick = false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
                if(!rotate_zClick){
                    rotate_z +=2;
                    rotate_zClick = true;
                }
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
                if(!rotate_zClick){
                    rotate_z -=2;
                    rotate_zClick = true;
                }
            }else{
                rotate_zClick = false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
                rotate_x = 0;
                rotate_y = 0;
                rotate_z = 0;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                for(auto& cube : cubes){
                }
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
                for(auto& cube : cubes){
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                for(auto& cube : cubes){
                    cube.transformcom.Move(Vector3D(0,0,-.01));
                }
                //camera.pos.z += .01;
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                for(auto& cube : cubes){
                    cube.transformcom.Move(Vector3D(0,0,.01));
                }                //camera.pos.z -= .01;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                for(auto& cube : cubes){
                    cube.transformcom.Move(Vector3D(-.01,0,0));
                }                //camera.pos.x += .01;
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                for(auto& cube : cubes){
                    cube.transformcom.Move(Vector3D(.01,0,0));
                }                //camera.pos.x -= .01;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                for(auto& cube : cubes){
                    cube.transformcom.Move(Vector3D(0,-.01,0));
                }                //camera.pos.y +=.01;
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                for(auto& cube : cubes){
                    cube.transformcom.Move(Vector3D(0,.01,0));
                }                //camera.pos.y -=.01;
            }
        }
        glRotatef(rotate_y,0.0,1.0,0.0);
        glRotatef(rotate_z,0.0,0.0,1.0);
        glRotatef(rotate_x,1.0,0.0,0.0);
        //cubes[0].Rotate(Vector3D(rotate_x,rotate_y,rotate_z));

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        //glDisable(GL_CULL_FACE);
        //glEnable(GL_CULL_FACE);

        for(auto& cube : cubes){
            cube.drawOnce(camera);
        }
        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;
}