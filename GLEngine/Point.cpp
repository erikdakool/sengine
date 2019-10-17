//
// Created by erik on 28.09.2019.
//

#include <math.h>
#include <iostream>

#include "Point.h"

Point::Point() {}

Point::~Point() {}

Point::Point(Vector3D v)
{
    matrix = Matrix<double>{
            {v.x},
            {v.y},
            {v.z},
            {1}
    };
}

Point::Point(double x, double y, double z)
{
    matrix = Matrix<double>{
            {x},
            {y},
            {z},
            {1}
    };
}

void Point::RotateX(double r) {
    Matrix<double> tMatrix ={
            {1,0,0,0},
            {0,cos(r),-sin(r),0},
            {0,sin(r),cos(r),0},
            {0,0,0,1}
    };
    this->matrix = tMatrix*this->matrix;
}

void Point::RotateY(double r) {
    Matrix<double> tMatrix ={
            {cos(r), 1, sin(r),0},
            {0, 1, 0,0},
            {-sin(r),0,cos(r),0},
            {0,0,0,1}
    };
    this->matrix = tMatrix*this->matrix;
}

void Point::RotateZ(double r) {
    Matrix<double> tMatrix ={
            {cos(r), -sin(r), 0,0},
            {sin(r), cos(r), 0,0},
            {0,0,1,0},
            {0,0,0,1}
    };
    this->matrix = tMatrix*this->matrix;
}

//Translate
void Point::Translate(Vector3D v) {
    Matrix<double> tMatrix ={
            {1, 0, 0, v.x},
            {0, 1, 0, v.y},
            {0, 0, 1, v.z},
            {0,0,0,1}
    };
    this->matrix = tMatrix*this->matrix;
}
void Point::Translate(Matrix<double> mat3) {
    Translate(Vector3D(mat3));
}
void Point::Translate(double x, double y, double z) {
    Translate(Vector3D(x,y,z));
}

//Scale
void Point::Scale(Vector3D v) {
    Matrix<double> tMatrix ={
            {v.x, 0, 0,0},
            {0, v.y, 0,0},
            {0, 0, v.z,0},
            {0,0,0,1}
    };
    this->matrix = tMatrix*this->matrix;
}
void Point::Scale(Matrix<double> mat3) {
    Translate(Vector3D(mat3));
}
void Point::Scale(double x, double y, double z) {
    Translate(Vector3D(x,y,z));
}


double* Point::getPointsDA() {
    static double ret[3];
    ret[0] = matrix[0][0];
    ret[1] = matrix[1][0];
    ret[2] = matrix[2][0];
    return ret;
}

Vector3D Point::getPointsV3() {
    return Vector3D(matrix[0][0],matrix[1][0],matrix[2][0]);
}

double Point::x() {
    return matrix[0][0];
}

double Point::y() {
    return matrix[1][0];
}

double Point::z() {
    return matrix[2][0];
}

void Point::x(double x) {
    matrix[0][0] = x;
}

void Point::y(double y) {
    matrix[1][0] = y;
}

void Point::z(double z) {
    matrix[2][0] = z;
}

void Point::print() {
    std::cout << "x " << matrix[0][0] << " y " << matrix[1][0] << " z " << matrix[2][0] << std::endl;
}
