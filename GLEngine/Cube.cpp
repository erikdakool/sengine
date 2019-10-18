//
// Created by erik on 28.09.2019.
//

#include "Cube.h"
#include <cmath>
#include <iostream>
#include <GL/gl.h>

using namespace std;

Cube::Cube():
Cube(0,0,0){}

Cube::~Cube() {}

Cube::Cube(const Vector3D& v):
Cube(v.x,v.y,v.z){}

Cube::Cube(double x, double y, double z) {
    points[0] = Point(0,0,0);
    points[1] = Point(x,0,0);
    points[2] = Point(x,0,z);
    points[3] = Point(0,0,z);
    points[4] = Point(0,y,0);
    points[5] = Point(x,y,0);
    points[6] = Point(x,y,z);
    points[7] = Point(0,y,z);
    anchor = Point(x/2,y/2,z/2);
}

void Cube::RotateX(double r) {
    for (int i = 0; i < 8; ++i) {
        points[i].Translate(-anchor.getPointsV3());
        points[i].RotateX(r);
        points[i].Translate(anchor.getPointsV3());
    }
}
void Cube::RotateY(double r) {
    for (int i = 0; i < 8; ++i) {
        points[i].Translate(-anchor.getPointsV3());
        points[i].RotateY(r);
        points[i].Translate(anchor.getPointsV3());
    }
}
void Cube::RotateZ(double r) {
    for (int i = 0; i < 8; ++i) {
        points[i].Translate(-anchor.getPointsV3());
        points[i].RotateZ(r);
        points[i].Translate(anchor.getPointsV3());
    }
}

void Cube::Rotate(Vector3D v) {
    transformcom.Rotate(v);
}

void Cube::m_Transform() {
    Matrix<double> mat = this->transformcom.getTransformMatrix();
    for (int i = 0; i < 8; ++i) {
        points[i].Transform(mat);
    }
}

void Cube::Translate(Vector3D v) {
    transformcom.Move(v);
}

void Cube::Scale(Vector3D v) {
    transformcom.Scale(v);
}

void Cube::draw() {
    //Back
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(.0f,1.0f,0.0f);
    glVertex3dv(points[2].getPointsDA());
    glVertex3dv(points[3].getPointsDA());
    glVertex3dv(points[6].getPointsDA());
    glVertex3dv(points[7].getPointsDA());
    glEnd();

    //Front
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1.0f, 0.0f, 0.0f);
    //glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3dv(points[0].getPointsDA());
    glVertex3dv(points[1].getPointsDA());
    glVertex3dv(points[4].getPointsDA());
    glVertex3dv(points[5].getPointsDA());
    glEnd();

    //Right
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1.0f,1.0f,0.0f);
    glVertex3dv(points[1].getPointsDA());
    glVertex3dv(points[2].getPointsDA());
    glVertex3dv(points[5].getPointsDA());
    glVertex3dv(points[6].getPointsDA());
    glEnd();

    //Left
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(.0f,1.0f,1.0f);
    glVertex3dv(points[0].getPointsDA());
    glVertex3dv(points[3].getPointsDA());
    glVertex3dv(points[4].getPointsDA());
    glVertex3dv(points[7].getPointsDA());
    glEnd();

    //Top
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(.0f,.0f,1.0f);
    glVertex3dv(points[4].getPointsDA());
    glVertex3dv(points[5].getPointsDA());
    glVertex3dv(points[7].getPointsDA());
    glVertex3dv(points[6].getPointsDA());
    glEnd();

    //Bottom
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1.0f,.0f,1.0f);
    glVertex3dv(points[0].getPointsDA());
    glVertex3dv(points[1].getPointsDA());
    glVertex3dv(points[3].getPointsDA());
    glVertex3dv(points[2].getPointsDA());
    glEnd();

    glFlush();
}

void Cube::drawOnce(Camera camera) {
    Matrix<double> tMatrix = transformcom.getTransformMatrix();
    Matrix<double> vMatrix = camera.getViewMatrix();
    Matrix<double> transform = camera.perspectiveMatrix * vMatrix * tMatrix;

    Point tpoints[8];
    copy(begin(points),end(points),begin(tpoints));
    for (int i = 0; i < 8; ++i) {

        tpoints[i].Transform(transform);
        //points[i].Transform(vMatrix);
    }

    //Front
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1.0f, 0.0f, 0.0f);
    //glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3dv(tpoints[0].getPointsDA());
    glVertex3dv(tpoints[1].getPointsDA());
    glVertex3dv(tpoints[4].getPointsDA());
    glVertex3dv(tpoints[5].getPointsDA());
    //Top
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3dv(tpoints[7].getPointsDA());
    glVertex3dv(tpoints[6].getPointsDA());
    //Back
    glColor3f(1.0f, .0f, 1.0f);
    glVertex3dv(tpoints[3].getPointsDA());
    glVertex3dv(tpoints[2].getPointsDA());
    //Bottom
    glColor3f(.0f, .0f, 1.0f);
    glVertex3dv(tpoints[0].getPointsDA());
    glVertex3dv(tpoints[1].getPointsDA());
    glEnd();

    //Right
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1.0f,1.0f,0.0f);
    glVertex3dv(tpoints[1].getPointsDA());
    glVertex3dv(tpoints[2].getPointsDA());
    glVertex3dv(tpoints[5].getPointsDA());
    glVertex3dv(tpoints[6].getPointsDA());
    glEnd();

    //Left
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(.0f,1.0f,1.0f);
    glVertex3dv(tpoints[0].getPointsDA());
    glVertex3dv(tpoints[3].getPointsDA());
    glVertex3dv(tpoints[4].getPointsDA());
    glVertex3dv(tpoints[7].getPointsDA());
    glEnd();
}
