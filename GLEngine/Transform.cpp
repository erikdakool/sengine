//
// Created by erik on 17.10.2019.
//

#include "Transform.h"

Transform::Transform() {
    rotation = Vector3D();
    pos = Vector3D();
    scale = Vector3D(1,1,1);
}

Transform::Transform(Vector3D rot, Vector3D pos, Vector3D scale) {
    this->rotation = rot;
    this-> pos = pos;
    this-> scale = scale;
}

Transform::~Transform() {

}

void Transform::Rotate(Vector3D v) {
    this->pos = this->pos + v;
}

void Transform::Move(Vector3D v) {
    this->pos = this->pos + v;
}

void Transform::Scale(Vector3D v) {
    this->pos = this->pos + v;
}