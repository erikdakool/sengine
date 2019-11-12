//
// Created by erik on 12.11.2019.
//

#include "InputManager.h"

InputManager::InputManager(GLFWwindow* window) {
    this->window = window;
}

InputManager::~InputManager() {

}

bool InputManager::isKeyPressed(int key) {
    return glfwGetKey(window,key);
}