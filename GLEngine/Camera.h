//
// Created by erik on 17.10.2019.
//

#ifndef GLENGINE_CAMERA_H
#define GLENGINE_CAMERA_H

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>

class Camera {
public:
    Camera();
    ~Camera();


public:
    const glm::mat4 &getViewMatrix();
    void setViewMatrix(const glm::mat4 &viewMatrix);

    const glm::mat4 &getPerspectiveMatrix() const;

    void setPerspectiveMatrix(const glm::mat4 &perspectiveMatrix);

    GLuint getMatrixId() const;

    void setMatrixId(GLuint matrixId);

    void moveForward(float r);
    void moveSide(float r);
    void moveUp(float r);
    void move(glm::vec3 v);
    void rotate(glm::vec3 v);
    GLuint programID;
private:
    glm::vec3 rotation;
    glm::vec3 pos;
    glm::vec3 center;
    glm::vec3 upVector;
    glm::mat4 viewMatrix;
    glm::mat4 perspectiveMatrix;
    GLuint  MatrixId;
    bool updateView = false;
    float xrot = 0;

};

#endif //GLENGINE_CAMERA_H
