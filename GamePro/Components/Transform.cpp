//
// Created by erik on 22.12.18.
//

#include "Transform.h"

Transform::Transform(Gameobject& gameobject)
:Component(gameobject)
{

}

Transform::Transform(Gameobject &gameobject, Json::Value input)
:Component(gameobject)
{
    Transform::setValuesJson(input);
}

Transform::~Transform() {

}

void Transform::init() {

}

void Transform::update(float deltaT) {

}

Json::Value Transform::getJson() {
    Json::Value ret;
    ret = Component::getCJson();
    ret["name"] = "transform";
    ret["x"] = x;
    ret["y"] = y;
    ret["xscale"] = xScale;
    ret["yscale"] = yScale;
    ret["rotation"] = rotation;
    return ret;
}

void Transform::setValuesJson(Json::Value input) {
    Component::setValuesJson(input);
    x = input["x"].asFloat();
    y = input["y"].asFloat();
    xScale = input["xscale"].asFloat();
    yScale = input["yscale"].asFloat();
    rotation = input["rotation"].asFloat();
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
