//
// Created by erik on 16.10.2019.
//

#include <iostream>
#include "Vector3D.h"

Vector3D::Vector3D() {

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

Vector3D Vector3D::operator-() {
    double rx = -x;
    if(rx == (-0))rx = 0;
    double ry = -y;
    if(ry ==(-0))ry =0;
    double rz = -z;
    if(rz ==(-0)) rz =0;
    return Vector3D(rx,ry,rz);
}