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

Cube::~Cube() {}

Cube::Cube(float x, float y, float z) {
    Point a(0,0,0);
    Point b(x,0,0);
    Point c(x,z,0);
    Point d(0,z,0);
    Point e(0,y,0);
    Point f(x,y,0);
    Point g(x,y,z);
    Point h(0,y,z);
}

/*
void Cube::Rotate(float r) {
    Matrix<float> tMatrix ={
            {cos(r), -sin(r), 0,0},
            {sin(r), cos(r), 0,0},
            {0,0,1,0},
            {0,0,0,1}
    };
    for (int i = 0; i < points.size(); ++i) {
        points[i] = tMatrix*points[i];
    }
}

void Cube::Translate(float x, float y,float z) {
    Matrix<float> tMatrix ={
            {1, 0, 0, x},
            {0, 1, 0, y},
            {0, 0, 1, z},
            {0,0,0,1}
    };
    for (int i = 0; i < points.size(); ++i) {
        points[i] = tMatrix*points[i];
    }
}

void Cube::Scale(float x, float y, float z) {
    Matrix<float> tMatrix ={
            {x, 0, 0,0},
            {0, y, 0,0},
            {0, 0, z,0},
            {0,0,0,1}
    };
    for (int i = 0; i < points.size(); ++i) {
        points[i] = tMatrix*points[i];
    }
}*/

void Cube::draw() {
    // draw...
    glBegin(GL_QUADS);
    // top
    glColor3f(1.0f, 0.0f, 0.0f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    glEnd();

    glBegin(GL_QUADS);
    // front
    glColor3f(0.0f, 1.0f,0.0f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    glEnd();

    glBegin(GL_QUADS);
    // right
    glColor3f(0.0f, 0.0f, 1.0f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);

    glVertex3f(0.5f, -0.5f, -0.5f);

    glEnd();

    glBegin(GL_QUADS);
    // left
    glColor3f(0.0f, 0.0f, 1.0f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);

    glEnd();

    glBegin(GL_QUADS);
    // bottom
    glColor3f(0.5f, 0.0f, 0.0f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);

    glEnd();

    glBegin(GL_QUADS);
    // back
    glColor3f(0.0f, 0.5f, 0.0f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd( );
}
