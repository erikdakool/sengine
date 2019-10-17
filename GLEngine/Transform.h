//
// Created by erik on 17.10.2019.
//

#ifndef GLENGINE_TRANSFORM_H
#define GLENGINE_TRANSFORM_H


#include "Vector3D.h"

class Transform {
public:
    Transform();
    Transform(Vector3D rot, Vector3D pos, Vector3D scale);
    ~Transform();

    void Rotate(Vector3D v);
    void Scale(Vector3D v);
    void Move(Vector3D v);

private:
    Vector3D rotation;
    Vector3D pos;
    Vector3D scale;
};


#endif //GLENGINE_TRANSFORM_H
