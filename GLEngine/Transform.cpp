//
// Created by erik on 18.10.2019.
//

#include <iostream>
#include "Transform.h"

Transform::Transform() {
    translate = glm::vec3(0.f,0.f,0.f);
    rotation = glm::vec3(0,0,0);
    scale = glm::vec3(1,1,1);
    transform = getTranslateMatrix() * getRotationMatrix() * getScaleMatrix();
}

Transform::~Transform() {

}

glm::mat4 Transform::getTranslateMatrix() {
    return glm::translate(glm::mat4(1.0f),translate);
}

glm::mat4 Transform::getRotationMatrix() {
    glm::mat4 rotX = glm::rotate(glm::mat4(1.0f),glm::radians(rotation.x),glm::vec3(1,0,0));
    glm::mat4 rotY = glm::rotate(glm::mat4(1.0f),glm::radians(rotation.y),glm::vec3(0,1,0));
    glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f),glm::radians(rotation.z),glm::vec3(0,0,1));
    return rotX * rotY * rotZ;
}

glm::mat4 Transform::getScaleMatrix() {
    return glm::scale(scale);
}

glm::mat4 Transform::getTransformMatrix() {
    if(updateTransform){
        transform = getTranslateMatrix() * getRotationMatrix() * getScaleMatrix();
        updateTransform = false;
    }
    return transform;
}

rp3d::Vector3 Transform::getRPVPosition() {
    return rp3d::Vector3(translate.x,translate.y,translate.z);
}

rp3d::Vector3 Transform::getRPVRotation() {
    return rp3d::Vector3(rotation.x,rotation.y,rotation.z);
}

void Transform::RotateX(float r) {
    rotation.x += r;
    updateTransform = true;
}

void Transform::RotateY(float r) {
    rotation.y += r;
    updateTransform = true;
}

void Transform::RotateZ(float r) {
    rotation.z += r;
    updateTransform = true;
}

void Transform::RotateAll(glm::vec3 r) {
    rotation += r;
    updateTransform = true;
}

void Transform::SetRotate(glm::vec3 v) {
    rotation = v;
    updateTransform = true;
}

void Transform::Scale(glm::vec3 v) {
    scale = v;
}

void Transform::move(glm::vec3 move) {
    translate = translate + move;
    updateTransform = true;
}