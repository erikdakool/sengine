//
// Created by erik on 12.11.2019.
//

#ifndef GLENGINE_INPUTMANAGER_H
#define GLENGINE_INPUTMANAGER_H


#include <GLFW/glfw3.h>

class InputManager {
public:
    InputManager() = default;
    explicit InputManager(GLFWwindow* window);
    ~InputManager();

    bool isKeyPressed(int key);

private:
    GLFWwindow* window;

};


#endif //GLENGINE_INPUTMANAGER_H
