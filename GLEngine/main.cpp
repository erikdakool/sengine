#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <math.h>
#include "Cube.h"

// compute screen coordinates first
void Perspective(
        const float &angleOfView,
        const float &imageAspectRatio,
        const float &n, const float &f,
        float &b, float &t, float &l, float &r)
{
    float scale = tan(angleOfView * 0.5 * M_PI / 180) * n;
    r = imageAspectRatio * scale, l = -r;
    t = scale, b = -t;
}

// set the OpenGL perspective projection matrix
void Frustum(
        const float &b, const float &t, const float &l, const float &r,
        const float &n, const float &f,
        Matrix<double> &M)
{
    // set OpenGL perspective projection matrix
    M[0][0] = 2 * n / (r - l);
    M[0][1] = 0;
    M[0][2] = 0;
    M[0][3] = 0;

    M[1][0] = 0;
    M[1][1] = 2 * n / (t - b);
    M[1][2] = 0;
    M[1][3] = 0;

    M[2][0] = (r + l) / (r - l);
    M[2][1] = (t + b) / (t - b);
    M[2][2] = -(f + n) / (f - n);
    M[2][3] = -1;

    M[3][0] = 0;
    M[3][1] = 0;
    M[3][2] = -2 * f * n / (f - n);
    M[3][3] = 0;
}

void multPointMatrix(const Vector3D &in, Vector3D &out, const Matrix<double> &M)
{
    //out = in * Mproj;
    out.x   = in.x * M[0][0] + in.y * M[1][0] + in.z * M[2][0] + /* in.z = 1 */ M[3][0];
    out.y   = in.x * M[0][1] + in.y * M[1][1] + in.z * M[2][1] + /* in.z = 1 */ M[3][1];
    out.z   = in.x * M[0][2] + in.y * M[1][2] + in.z * M[2][2] + /* in.z = 1 */ M[3][2];
    float w = in.x * M[0][3] + in.y * M[1][3] + in.z * M[2][3] + /* in.z = 1 */ M[3][3];

    // normalize if w is different than 1 (convert from homogeneous to Cartesian coordinates)
    if (w != 1) {
        out.x /= w;
        out.y /= w;
        out.z /= w;
    }
}

int main()
{
    Vector3D a = Vector3D(1,2,3);
    Vector3D b = Vector3D(2,3,4);

    double rotate_x = 0;
    bool rotate_xClick =false;
    double rotate_y = 0;
    bool rotate_yClick = false;
    double rotate_z = 0;
    bool rotate_zClick = false;
    Vector3D camera = Vector3D(0,0,0);

    Cube floor = Cube(2,.1,2);
    floor.Translate(Vector3D(-1,-1,-1));

    std::vector<Cube> cubes;
    cubes.emplace_back(.4,.4,.4);
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

    sf::Window window(sf::VideoMode(800, 800), "OpenGL", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    // activate the window
    window.setActive(true);

    // load resources, initialize the OpenGL states, ...

    // run the main loop

    glViewport(0,0, 800, 800);

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
                    cube.Scale(Vector3D(.9,.9,.9));
                }
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
                for(auto& cube : cubes){
                    cube.Scale(Vector3D(1.1,1.1,1.1));
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                camera.z += .01;
                cubes[0].Scale(Vector3D(1.01,1.01,1.01));
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                camera.z -= .01;
                cubes[0].Scale(Vector3D(0.99,0.99,0.99));
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                camera.x += .01;
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                camera.x -= .01;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                camera.y +=.01;
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                camera.y -=.01;
            }
        }
        glRotatef(rotate_y,0.0,1.0,0.0);
        glRotatef(rotate_z,0.0,0.0,1.0);
        glRotatef(rotate_x,1.0,0.0,0.0);
        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        //glEnable(GL_CULL_FACE);

        floor.drawOnce(camera);
        for(auto& cube : cubes){
            cube.Translate(-camera);
            cube.drawOnce(camera);
        }
        camera.x = 0; camera.y = 0; camera.z = 0;
        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;
}