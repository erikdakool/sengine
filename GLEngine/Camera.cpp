//
// Created by erik on 17.10.2019.
//

#include "Camera.h"
Camera::Camera() {
    pos = Vector3D(0,0,0);
    rot = Vector3D(0,0,0);
    upVector = Vector3D(0,1,0);
}

Camera::~Camera() {

}

Matrix<double> Camera::getViewMatrix() {
    Matrix<double> tMatrix ={
            {1, 0, 0, pos.x},
            {0, 1, 0, pos.y},
            {0, 0, 1, pos.z},
            {0,0,0,1}
    };
    return tMatrix;
}