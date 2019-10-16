//
// Created by erik on 28.09.2019.
//

#ifndef GLENGINE_POINT_H
#define GLENGINE_POINT_H

#include "Matrix.h"
#include "Vector3D.h"

class Point {
public:
    Point();
    Point(Vector3D v);
    Point(double x, double y, double z);
    ~Point();

    double x();
    double y();
    double z();

    void RotateX(double r);
    void RotateY(double r);
    void RotateZ(double r);
    void Translate(Vector3D v);
    void Scale(Vector3D v);

    void x(double x);
    void y(double y);
    void z(double z);
    double* getPointsDA();
    Vector3D getPointsV3();

    Vector3D PointDiff(Point& in);
    void print();

private:
    Matrix<double> matrix;
};


#endif //GLENGINE_POINT_H
