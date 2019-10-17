//
// Created by erik on 16.10.2019.
//

#include <iostream>
#include "Vector3D.h"

Vector3D::Vector3D() {
    x = 0;
    y = 0;
    z = 0;
}

Vector3D::Vector3D(Matrix<double> mat) {
    x = mat[0][0];
    y = mat[1][0];
    z = mat[2][0];
}

Vector3D::Vector3D(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3D::~Vector3D() {}

void Vector3D::print() {
    std::cout << "x " << x << " y " << y << " z " << z << std::endl;
}

Matrix<double> Vector3D::mat3() {
    Matrix<double> ret = {
            {x},
            {y},
            {z},
    };
    return ret;
}

Matrix<double> Vector3D::mat4() {
    Matrix<double> ret = {
            {x},
            {y},
            {z},
            {1}
    };
    return ret;
}

Vector3D Vector3D::operator-() {
    double rx = -x;
    if(rx == (-0))rx = 0;
    double ry = -y;
    if(ry ==(-0))ry =0;
    double rz = -z;
    if(rz ==(-0)) rz =0;
    return Vector3D(rx,ry,rz);
}

Vector3D Vector3D::operator-(const Vector3D &in) {
    double dx = this-> x - in.x;
    double dy = this-> y - in.y;
    double dz = this-> z - in.z;
    return Vector3D(dx,dy,dz);
}

Vector3D Vector3D::operator+(const Vector3D &in) {
    double dx = this-> x + in.x;
    double dy = this-> y + in.y;
    double dz = this-> z + in.z;
    return Vector3D(dx,dy,dz);
}

Vector3D& Vector3D::operator+=(const Vector3D &in) {
    this->x += in.x;
    this->y += in.y;
    this->z += in.z;
    return *this;
}