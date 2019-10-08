//
// Created by erik on 28.09.2019.
//

#ifndef GLENGINE_POINT_H
#define GLENGINE_POINT_H

#include "Matrix.h"

class Point {
public:
    Point();
    Point(float x, float y, float z);
    float x();
    float y();
    float z();

    void Rotate(float r);
    void Translate(float x, float y, float z);
    void Scale(float x, float y, float z);

    void x(float x);
    void y(float y);
    void z(float z);

private:
    Matrix<float> matrix;
};


#endif //GLENGINE_POINT_H
