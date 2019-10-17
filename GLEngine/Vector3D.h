//
// Created by erik on 16.10.2019.
//

#ifndef GLENGINE_VECTOR3D_H
#define GLENGINE_VECTOR3D_H

#include "Matrix.h"

class Vector3D {
public:
    Vector3D();
    explicit Vector3D(Matrix<double> mat);
    Vector3D(double x, double y, double z);
    ~Vector3D();
    void print();

    Matrix<double> mat4();
    Matrix<double> mat3();
    Vector3D operator -();
    Vector3D operator -(const Vector3D& in);
    Vector3D operator +(const Vector3D& in);
    Vector3D&operator +=(const Vector3D& in);
    double x;
    double y;
    double z;
};

#endif //GLENGINE_VECTOR3D_H
