//
// Created by erikdesk on 7/4/20.
//

#ifndef GLENGINE_POINTMATH_H
#define GLENGINE_POINTMATH_H

#include <math.h>
#include <glm/glm.hpp>
bool insideFov(float v,glm::vec2 objectLoc, glm::vec2 playerLoc, glm::vec2 coneVector);
bool inRange(float low, float high, float x);
#endif //GLENGINE_POINTMATH_H
