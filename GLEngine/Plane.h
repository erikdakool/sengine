//
// Created by erik on 28.09.2019.
//

#ifndef GLENGINE_PLANE_H
#define GLENGINE_PLANE_H


#include "Matrix.h"
#include "Point.h"
class Plane {
public:
    Plane(float x, float y);
    ~Plane();

    void Rotate(float r);
    void Translate(float x, float y, float z);
    void Scale(float x, float y, float z);
    void draw();

private:
    Point points[4];
};


#endif //GLENGINE_PLANE_H
