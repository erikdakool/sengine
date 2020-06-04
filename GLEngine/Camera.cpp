//
// Created by erik on 17.10.2019.
//

#include <iostream>
#include "Camera.h"

Camera::Camera() {
    rotation = glm::vec3(0,-90,0);
    pos = glm::vec3(400,400,600);
    center = glm::vec3(0,0,-1);
    upVector = glm::vec3(0,1,0);
    viewMatrix = glm::lookAt(
            pos,pos+center,upVector
            );
}

Camera::~Camera() {

}

const glm::mat4& Camera::getViewMatrix(){
    if(updateView){
        this->viewMatrix = glm::lookAt(
                pos,pos+center,upVector
        );
        glm::mat4 rotX = glm::rotate(glm::mat4(1.0f),glm::radians(rotation.x),glm::vec3(1,0,0));
        glm::mat4 rotY = glm::rotate(glm::mat4(1.0f),glm::radians(rotation.y),glm::vec3(0,1,0));
        glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f),glm::radians(rotation.z),glm::vec3(0,0,1));
    }
    return viewMatrix;
}

void Camera::setViewMatrix(const glm::mat4 &viewMatrix) {
    Camera::viewMatrix = viewMatrix;
}

const glm::mat4 &Camera::getPerspectiveMatrix() const {
    return perspectiveMatrix;
}

void Camera::setPerspectiveMatrix(const glm::mat4 &perspectiveMatrix) {
    Camera::perspectiveMatrix = perspectiveMatrix;
}

GLuint Camera::getMatrixId() const {
    return MatrixId;
}

void Camera::setMatrixId(GLuint matrixId) {
    MatrixId = matrixId;
}

void Camera::move(glm::vec3 v) {
    pos += v;
    updateView = true;
}

void Camera::moveForward(float r) {
    pos.z += r*sin(glm::radians(rotation.y));
    pos.x += r*cos(glm::radians(rotation.y));
    updateView = true;
}

void Camera::moveSide(float r) {
    pos.z += r*sin(glm::radians(rotation.y+90));
    pos.x += r*cos(glm::radians(rotation.y+90));
    updateView = true;
}

void Camera::moveUp(float r) {
    pos.y += r;
    updateView = true;
}

void Camera::rotate(glm::vec3 v) {
    rotation += v;
    if(rotation.x > 89.0f){
        rotation.x = 89.0f;
    }
    if(rotation.x < -89.0f){
        rotation.x = -89.0f;
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
    direction.y = sin(glm::radians(rotation.x));
    direction.z = cos(glm::radians(rotation.x)) * sin(glm::radians(rotation.y));
    center = glm::normalize(direction);
    updateView = true;
    //std::cout << "Rotation: " << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;
    //std::cout << "Position: " << pos.x << " " << pos.y << " " << pos.z << std::endl;
}