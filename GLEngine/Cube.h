//
// Created by erik on 28.09.2019.
//

#ifndef GLENGINE_CUBE_H
#define GLENGINE_CUBE_H

#include <memory>
#include <vector>

#include "Matrix.h"
#include "SFML/Graphics.hpp"
#include "Point.h"

using namespace std;
class Cube {
public:
    Cube();
    Cube(Vector3D v);
    Cube(double x, double y, double z);
    ~Cube();

    void RotateX(double r);
    void RotateY(double r);
    void RotateZ(double r);
    void Translate(Vector3D v);
    void Scale(Vector3D v);
    void draw();
private:
   Point points[8];
   Point anchor;
};


#endif //GLENGINE_CUBE_H
