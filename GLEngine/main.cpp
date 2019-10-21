// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "AssetController.h"

using namespace glm;

#include "shader.hpp"
#include "Triangle.h"
#include "Camera.h"
#include "Cube.h"

#define GLM_ENABLE_EXPERIMENTAL

GLFWwindow* window;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

float fov = 60;
float width = 1600.0f;
float height = 1200.0f;
float near = 0.1f;
float far = 100.0f;
Camera camera = Camera();
double previousTime = glfwGetTime();
int frameCount = 0;

int main( void )
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    //glfwWindowHint(GLFW_DOUBLEBUFFER,GL_FALSE);
    window = glfwCreateWindow( width, height, "Tutorial 02 - Red triangle", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window,mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);


    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);


    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "SimpleVertexShader.glsl", "SimpleFragmentShader.glsl" );
    camera.programID = programID;
    camera.setPerspectiveMatrix(glm::perspective(glm::radians(fov),width/height,near,far));
    camera.setMatrixId(glGetUniformLocation(programID,"MVP"));

    AssetController assetController = AssetController();

    Triangle triangle = Triangle();
    std::vector<Cube> cubes;
    cubes.push_back(Cube(glm::vec3(1,1,1),assetController));
    cubes.push_back(Cube(glm::vec3(10,1,10),assetController));
    cubes.push_back(Cube(glm::vec3(1,1,1),assetController));
    cubes.push_back(Cube(glm::vec3(1,1,1),assetController));

    cubes[0].transform.move(glm::vec3(10,0,10));
    cubes[1].transform.move(glm::vec3(0,-10,0));
    cubes[2].transform.move(glm::vec3(0,0,10));
    cubes[3].transform.move(glm::vec3(10,0,0));

    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            Cube cube = Cube(glm::vec3(2,2,2),assetController);
            cube.transform.move(glm::vec3(10+x*2,-10,y*2));
            cubes.push_back(cube);
        }
    }

    do{
        double currentTime = glfwGetTime();
        frameCount++;
        if(currentTime - previousTime >=1.0){
            std::cout << frameCount << std::endl;
            frameCount = 0;
            previousTime = currentTime;
        }
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);

        if(glfwGetKey(window,GLFW_KEY_U) == GLFW_PRESS){
            cubes[0].transform.RotateY(5);
        }
        if(glfwGetKey(window,GLFW_KEY_O) == GLFW_PRESS){
            cubes[0].transform.RotateY(-5);
        }

        if(glfwGetKey(window,GLFW_KEY_I) == GLFW_PRESS){
            cubes[0].transform.RotateX(5);
        }
        if(glfwGetKey(window,GLFW_KEY_K) == GLFW_PRESS){
            cubes[0].transform.RotateX(-5);
        }

        if(glfwGetKey(window,GLFW_KEY_J) == GLFW_PRESS){
            cubes[0].transform.RotateZ(5);
        }
        if(glfwGetKey(window,GLFW_KEY_L) == GLFW_PRESS){
            cubes[0].transform.RotateZ(-5);
        }if(glfwGetKey(window,GLFW_KEY_P)==GLFW_PRESS){
            cubes[0].transform.SetRotate(glm::vec3(0,0,0));
        }

        if(glfwGetKey(window,GLFW_KEY_Q) == GLFW_PRESS) {
            camera.moveUp(-1);
        }
        if(glfwGetKey(window,GLFW_KEY_E) == GLFW_PRESS) {
            camera.moveUp(1);
        }
        if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS) {
            camera.moveForward(1);
        }
        if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS) {
            camera.moveForward(-1);
        }
        if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS) {
            camera.moveSide(1);
        }
        if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS) {
            camera.moveSide(-1);
        }

        if(glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS) {
            camera.rotate(glm::vec3(0,-5,0));
        }
        if(glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS) {
            camera.rotate(glm::vec3(0,5,0));
        }
        if(glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS) {
            camera.rotate(glm::vec3(5,0,0));
        }
        if(glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS) {
            camera.rotate(glm::vec3(-5,0,0));
        }
        if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS) {
        }

        // Draw the triangle !
        //glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
        triangle.Draw(camera);
        for(auto & cube : cubes){
            cube.Draw(camera);
        }
        glDisableVertexAttribArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Cleanup VBO
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    glfwSetCursorPos(window,width/2,height/2);
    float yoffset = (-1.f) * .1f* (float)(width/2 - xpos);
    float xoffset = .1f* (float)(height/2 - ypos);

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    glm::vec3 rotate = glm::vec3(xoffset,yoffset,0);
    camera.rotate(rotate);
}