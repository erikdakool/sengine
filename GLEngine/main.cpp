// Include standard headers
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <memory>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include "Managers/shader.hpp"
#include "Camera.h"
#include "Gameobject/Cube.h"
#include "Gameobject/Gameobject.h"
#include "Managers.h"
#include "Components/Renderer.h"
#include "Components/Physics.h"
#include "Components/Collider.h"
#include "Gameobject/Excavator.h"


#define GLM_ENABLE_EXPERIMENTAL
GLFWwindow* window;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);


GameDataRef _data;

float fov = 60;
float width = 1600.0f;
float height = 1200.0f;
float near = 0.1f;
float far = 1000.0f;
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
    window = glfwCreateWindow( width, height, "Excavator simulator", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


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
    glfwSetCursorPosCallback(window,mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "SimpleVertexShader.glsl", "SimpleFragmentShader.glsl" );

    _data = std::make_shared<GameData>();
    _data->camera = Camera();
    _data->textureLoader = TextureLoader();
    _data->modelLoader = ModelLoader();
    _data->objectManager = ObjectManager();
    _data->inputManager = InputManager(window);

    _data->camera.programID = programID;
    _data->camera.setPerspectiveMatrix(glm::perspective(glm::radians(fov),width/height,near,far));
    _data->camera.setMatrixId(glGetUniformLocation(programID,"MVP"));

    TextureLoader textureLoader = TextureLoader();

    auto gameobject = std::make_shared<Excavator>(_data);
    _data.get()->objectManager.AddObject(gameobject);

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

        if(glfwGetKey(window,GLFW_KEY_Q) == GLFW_PRESS) {
            _data->camera.moveUp(-1);
        }
        if(glfwGetKey(window,GLFW_KEY_E) == GLFW_PRESS) {
            _data->camera.moveUp(1);
        }
        if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS) {
            _data->camera.moveForward(1);
        }
        if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS) {
            _data->camera.moveForward(-1);
        }
        if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS) {
            _data->camera.moveSide(1);
        }
        if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS) {
            _data->camera.moveSide(-1);
        }

        _data.get()->objectManager.UpdateAll(1.f);

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
    _data->camera.rotate(rotate);
}