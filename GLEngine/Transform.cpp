//
// Created by erik on 18.10.2019.
//

#include <iostream>
#include "Transform.h"
#include "Gameobject/Gameobject.h"
Transform::Transform(Gameobject& gameobject)
:gameobject(gameobject)
{
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
    if(rotation.y > 360 && rotation.y > 0){
        rotation.y -= 360;
    }

    if(rotation.y < 360 && rotation.y < 0){
        rotation.y += 360;
    }

    glm::mat4 rotX = glm::rotate(glm::mat4(1.0f),glm::radians(rotation.x),glm::vec3(1,0,0));
    glm::mat4 rotY = glm::rotate(glm::mat4(1.0f),glm::radians(rotation.y),glm::vec3(0,1,0));
    glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f),glm::radians(rotation.z),glm::vec3(0,0,1));
    return rotZ * rotY * rotX;
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

glm::vec3 Transform::getRotation() {
    return rotation;
}

glm::vec3 Transform::RotateAroundPointY(glm::vec3 point, float r) {
    glm::vec3 origo = translate - point;
    glm::vec4 v(origo,1);
    glm::mat4 rotY = glm::rotate(glm::mat4(1.0f),glm::radians(r),glm::vec3(0,1,0));
    glm::vec newpoint = rotY * v;
    translate = newpoint + glm::vec4(point.x,point.y,point.z,0);
    updateTransform = true;
    return newpoint;
}

glm::vec3 Transform::RotateAroundPointX(glm::vec3 point, float r) {
    glm::vec3 origo = translate - point;
    glm::vec4 v(origo,1);
    glm::mat4 rotX = glm::rotate(glm::mat4(1.0f),glm::radians(r),glm::vec3(1,0,0));
    glm::vec4 newpoint = rotX * v;
    auto ret = translate - (glm::vec3(newpoint.x,newpoint.y,newpoint.z) + point);
    translate = newpoint + glm::vec4(point.x,point.y,point.z,0);
    updateTransform = true;
    return ret;
}

glm::vec3 Transform::RotateAroundPointZ(glm::vec3 point, float r) {
    glm::vec3 origo = translate - point;
    glm::vec4 v(origo,1);
    glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f),glm::radians(r),glm::vec3(0,0,1));
    glm::vec newpoint = rotZ * v;
    auto ret = translate - (glm::vec3(newpoint.x,newpoint.y,newpoint.z) + point);
    translate = newpoint + glm::vec4(point.x,point.y,point.z,0);
    updateTransform = true;
    return ret;
}

void Transform::Scale(glm::vec3 v) {
    scale = v;
    updateTransform = true;
}

void Transform::Scale(float scale){
     this->scale = glm::vec3(scale);

}

void Transform::move(glm::vec3 move) {
    translate = translate + move;
    updateTransform = true;
    for(auto& child: gameobject.getChildren()){
        child.get()->transform().move(move);
    }
}

glm::vec3 Transform::getPosition() {
    return translate;
}