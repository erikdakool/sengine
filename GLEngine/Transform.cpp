//
// Created by erik on 17.10.2019.
//

#include <cmath>
#include "Transform.h"

Transform::Transform() {
    rotation = Vector3D();
    pos = Vector3D();
    scale = Vector3D(1,1,1);
}

Transform::Transform(Vector3D rot, Vector3D pos, Vector3D scale) {
    this->rotation = rot;
    this-> pos = pos;
    this-> scale = scale;
}

Transform::~Transform() {

}

void Transform::Rotate(Vector3D v) {
    this->pos+=v;
}

void Transform::Move(Vector3D v) {
    this->pos+=v;
}

void Transform::Scale(Vector3D v) {
    this->pos+=v;
}

Vector3D Transform::getrot() {
    return rotation;
}

Vector3D Transform::getscale() {
    return scale;
}

Vector3D Transform::getpos() {
    return pos;
}

Matrix<double> Transform::getRotationMatrix() {
    Matrix<double> zMatrix = {
            {cos(rotation.z), -sin(rotation.z), 0, 0},
            {sin(rotation.z), cos(rotation.z),  0, 0},
            {0,               0,                1, 0},
            {0,               0,                0, 1}
    };
    Matrix<double> yMatrix = {
            {cos(rotation.y),  1, sin(rotation.y), 0},
            {0,                1, 0,               0},
            {-sin(rotation.y), 0, cos(rotation.y), 0},
            {0,                0, 0,               1}
    };
    Matrix<double> xMatrix = {
            {1, 0,               0,                0},
            {0, cos(rotation.x), -sin(rotation.x), 0},
            {0, sin(rotation.x), cos(rotation.x),  0},
            {0, 0,               0,                1}
    };
    return yMatrix*xMatrix*zMatrix;
}

Matrix<double> Transform::getTranslateMatrix() {
    Matrix<double> tMatrix ={
            {1, 0, 0, pos.x},
            {0, 1, 0, pos.y},
            {0, 0, 1, pos.z},
            {0,0,0,1}
    };
    return tMatrix;
}

Matrix<double> Transform::getScaleMatrix() {
    Matrix<double> tMatrix ={
            {scale.x, 0, 0,0},
            {0, scale.y, 0,0},
            {0, 0, scale.z,0},
            {0,0,0,1}
    };
    return tMatrix;
}

Matrix<double> Transform::getTransformMatrix(){
    return getTranslateMatrix() * getScaleMatrix();
}