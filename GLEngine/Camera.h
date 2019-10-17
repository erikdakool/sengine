//
// Created by erik on 17.10.2019.
//

#ifndef GLENGINE_CAMERA_H
#define GLENGINE_CAMERA_H


#include "Vector3D.h"

class Camera {
public:
    Camera();
    ~Camera();
    Vector3D pos;
    Vector3D rot;
    Vector3D upVector;
    Matrix<double> getViewMatrix();
    Matrix<double> perspectiveMatrix;
};


#endif //GLENGINE_CAMERA_H
