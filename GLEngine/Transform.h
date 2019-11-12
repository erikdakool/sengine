//
// Created by erik on 18.10.2019.
//

#ifndef GLENGINE_TRANSFORM_H
#define GLENGINE_TRANSFORM_H

#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <reactphysics3d/reactphysics3d.h>


class Transform {
public:
    Transform();
    ~Transform();

    glm::mat4 getTranslateMatrix();
    glm::mat4 getRotationMatrix();
    glm::mat4 getScaleMatrix();
    glm::mat4 getTransformMatrix();

    rp3d::Vector3 getRPVPosition();
    rp3d::Vector3 getRPVRotation();

    void RotateX(float r);
    void RotateY(float r);
    void RotateZ(float r);
    glm::vec3 getRotation();
    void RotateAll(glm::vec3 r);
    void SetRotate(glm::vec3 v);
    void Scale(glm::vec3 v);
    void move(glm::vec3 move);

private:
    glm::vec3 translate;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 transform;
    bool updateTransform = false;
};


#endif //GLENGINE_TRANSFORM_H
