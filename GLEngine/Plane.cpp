//
// Created by erik on 28.09.2019.
//

#include "Plane.h"
#include <GL/gl.h>

Plane::Plane(float x, float y) {
    Point a(0,0,0);
    Point b(x,0,0);
    Point c(x,y,0);
    Point d(0,y,0);

    this->points[0] = a;
    this->points[1] = b;
    this->points[2] = c;
    this->points[3] = d;
}

Plane::~Plane() {}

void Plane::Rotate(float r) {
    for (auto & point : points) {
        point.Rotate(r);
    }
}

void Plane::Scale(float x, float y, float z) {
    for (auto & point : points) {
        point.Scale(x,y,z);
    }
}

void Plane::Translate(float x, float y, float z) {
    for (auto & point : points) {
        point.Translate(x,y,z);
    }
}

void Plane::draw() {
    glBegin(GL_QUADS);
    glColor3f(1.0f,0.0f,0.0f);
 //   glNormal3f(0.0f,0.0f,1.0f);
    for(auto & point : points){
        glVertex3f(point.x(),point.y(),point.z());
    }
    glEnd();
}