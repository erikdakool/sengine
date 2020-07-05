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
#include <thread>
#include <zconf.h>


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
#include "Components/NoclipController.h"
#include "Managers/ChunkManager.h"
#include "Managers/TerrainGenerator.h"
#include "Shader/ShaderGenerator.cpp"

#define GLM_ENABLE_EXPERIMENTAL
GLFWwindow* window;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);


GameDataRef data;

float fov = FOV;
float width = 2400.0f;
float height = 1600.0f;
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
    //glClearColor(1,0,1, 1);
    glClearColor(0.1,0.1,0.1,1);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Create and compile our GLSL program from the shaders
    GLuint modelProgramId = LoadShaders("Shader/ColorVertexShader.glsl", "Shader/ColorFragmentShader.glsl" );
    //GLuint modelProgramId = LoadShaders( "Shader/SimpleVertexShader.glsl", "Shader/SimpleFragmentShader.glsl" );
    glUseProgram(modelProgramId);

    data = std::make_shared<GameData>();
    data->camera = Camera();
    //data->camera.rotate(glm::vec3(-36,-20,0));
    data->textureLoader = TextureLoader();
    data->modelLoader = ModelLoader();
    data->objectManager = ObjectManager();
    data->inputManager = InputManager(window);

    data->camera.setModelProgramId(modelProgramId);

    data->camera.setPerspectiveMatrix(glm::perspective(glm::radians(fov),width/height,near,far));
    data->camera.setMatrixId(glGetUniformLocation(modelProgramId, "MVP"));

    TextureLoader textureLoader = TextureLoader();


    //auto excavator = std::make_shared<Excavator>(data);
    //data.get()->objectManager.AddObject(excavator);
    //glDeleteBuffers;

    auto brick  = std::make_shared<Gameobject>(data);
    //auto renderer = std::make_shared<Renderer>(*brick,data,"cube","Data/cube.obj");
    auto noclip = std::make_shared<NoclipController>(*brick,data);
    brick.get()->AddComponent(noclip);
    //brick.get()->AddComponent(renderer);

    data.get()->objectManager.AddObject(brick);
    brick.get()->transform().move(glm::vec3(0,3,-2));
    brick.get()->transform().Scale(glm::vec3(1,1,1));

    //ChunkManager blockManager(data);

    TerrainGenerator terrainGenerator(data);

   //blockManager.AddBlock(glm::vec3(0,0,0),"cobble",1,Stone);
   //blockManager.AddBlock(glm::vec3(3,0,0),"cobble",1,Grass);
   //blockManager.AddBlock(glm::vec3(6,0,0),"cobble",1,Dirt);

    //Vsync on/off
    glfwSwapInterval(1);

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
        glClearDepth(GL_DEPTH_BUFFER);
        // Use our shader
        glUseProgram(modelProgramId);
        //glClearColor(1,0,1, 1);
        //glBindTextureUnit(2,textureId);

        if(glfwGetKey(window,GLFW_KEY_Q) == GLFW_PRESS) {
            data->camera.moveUp(-1);
        }
        if(glfwGetKey(window,GLFW_KEY_E) == GLFW_PRESS) {
            data->camera.moveUp(1);
        }
        if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS) {
            data->camera.moveForward(1);
        }
        if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS) {
            data->camera.moveForward(-1);
        }
        if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS) {
            data->camera.moveSide(1);
        }
        if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS) {
            data->camera.moveSide(-1);
        }

        //data.get()->objectManager.UpdateAll(1.f);
        terrainGenerator.Update();
      //  blockManager.Draw();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        //usleep(100*1000);

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );


    // Cleanup VBO
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(modelProgramId);
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
    data->camera.rotate(rotate);
}