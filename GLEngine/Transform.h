//
// Created by erik on 18.10.2019.
//

#ifndef GLENGINE_TRANSFORM_H
#define GLENGINE_TRANSFORM_H

#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

class Gameobject;
class Transform {
public:
    Transform(Gameobject& gameobject);
    ~Transform();

    glm::mat4 getTranslateMatrix();
    glm::mat4 getRotationMatrix();
    glm::mat4 getScaleMatrix();
    glm::mat4 getTransformMatrix();

    void RotateX(float r);
    void RotateY(float r);
    void RotateZ(float r);
    glm::vec3 getRotation();
    void RotateAll(glm::vec3 r);
    void SetRotate(glm::vec3 v);

    glm::vec3 RotateAroundPointY(glm::vec3 point,float r);
    glm::vec3 RotateAroundPointX(glm::vec3 point,float r);
    glm::vec3 RotateAroundPointZ(glm::vec3 point,float r);

    void Scale(glm::vec3 v);
    void Scale(float scale);
    void move(glm::vec3 move);
    glm::vec3 getPosition();
private:
    glm::vec3 translate;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 transform;
    bool updateTransform = false;
    Gameobject& gameobject;
};


#endif //GLENGINE_TRANSFORM_H
