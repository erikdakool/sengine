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
    Cube(float x, float y, float z);
    ~Cube();

    void Rotate(float r);
    void Translate(float x, float y, float z);
    void Scale(float x, float y, float z);

    void draw();

private:
    Matrix<float> points[8];
};


#endif //GLENGINE_CUBE_H
