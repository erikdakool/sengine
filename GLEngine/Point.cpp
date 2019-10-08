//
// Created by erik on 28.09.2019.
//

#include <math.h>

#include "Point.h"

Point::Point() {}

Point::Point(float x, float y, float z)
{
    x = x;
    y = y;
    z = z;
    matrix = Matrix<float>{
            {x},
            {y},
            {z},
            {1}
    };
}

void Point::Rotate(float r) {
    Matrix<float> tMatrix ={
            {cos(r), -sin(r), 0,0},
            {sin(r), cos(r), 0,0},
            {0,0,1,0},
            {0,0,0,1}
    };
    this->matrix = tMatrix*this->matrix;
}

void Point::Translate(float x, float y,float z) {
    Matrix<float> tMatrix ={
            {1, 0, 0, x},
            {0, 1, 0, y},
            {0, 0, 1, z},
            {0,0,0,1}
    };
    this->matrix = tMatrix*this->matrix;
}

void Point::Scale(float x, float y, float z) {
    Matrix<float> tMatrix ={
            {x, 0, 0,0},
            {0, y, 0,0},
            {0, 0, z,0},
            {0,0,0,1}
    };
    this->matrix = tMatrix*this->matrix;
}

float Point::x() {
    return matrix[0][0];
}

float Point::y() {
    return matrix[1][0];
}

float Point::z() {
    return matrix[2][0];
}

void Point::x(float x) {
    matrix[0][0] = x;
}

void Point::y(float y) {
    matrix[0][1] = y;
}

void Point::z(float z) {
    matrix[0][2] = z;
}