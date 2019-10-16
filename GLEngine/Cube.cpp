//
// Created by erik on 28.09.2019.
//

#include "Cube.h"
#include <cmath>
#include <iostream>
#include <GL/gl.h>

using namespace std;

Cube::Cube() {

}

Cube::~Cube() {

}

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

void Cube::Translate(Vector3D v) {
    for (int i = 0; i < 8; ++i) {
        points[i].Translate(v);
    }
    anchor.Translate(v);
}

void Cube::Scale(Vector3D v) {

    for (int i = 0; i < 8; ++i) {
        points[i].Translate(-anchor.getPointsV3());
        points[i].Scale(v);
        points[i].Translate(anchor.getPointsV3());
    }
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
