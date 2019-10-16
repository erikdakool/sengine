//
// Created by erik on 16.10.2019.
//

#ifndef GLENGINE_VECTOR3D_H
#define GLENGINE_VECTOR3D_H


class Vector3D {
public:
    Vector3D();
    Vector3D(double x, double y, double z);
    ~Vector3D();

    void print();

    Vector3D operator -();


    double x;
    double y;
    double z;
};


#endif //GLENGINE_VECTOR3D_H
