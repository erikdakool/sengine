//
// Created by erik on 22.12.18.
//

#include "Transform.h"

Transform::Transform() {

}

Transform::~Transform() {

}

void Transform::increaseX(float value) {
    x+=value;
}

void Transform::decreaseX(float value) {
    x-=value;
}

void Transform::increaseY(float value) {
    y+=value;
}

void Transform::decreaseY(float value) {
    y-=value;
}

void Transform::rotateD(float value) {
    rotation+=value;
}

float Transform::getX() const {
    return x;
}

void Transform::setX(float x) {
    Transform::x = x;
}

float Transform::getY() const {
    return y;
}

void Transform::setY(float y) {
    Transform::y = y;
}

float Transform::getXScale() const {
    return xScale;
}

void Transform::setXScale(float xScale) {
    Transform::xScale = xScale;
}

float Transform::getYScale() const {
    return yScale;
}

void Transform::setYScale(float yScale) {
    Transform::yScale = yScale;
}

float Transform::getRotation() const {
    return rotation;
}

void Transform::setRotation(float rotation) {
    Transform::rotation = rotation;
}
