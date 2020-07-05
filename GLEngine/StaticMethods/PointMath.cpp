//
// Created by erikdesk on 7/5/20.
//

#include "PointMath.h"
#include "../Camera.h"

bool insideFov(float v, glm::vec2 objectLoc, glm::vec2 playerLoc, glm::vec2 coneVector){
    auto point_vector = normalize(objectLoc - playerLoc);
    float dot_product = dot(glm::normalize(coneVector), point_vector);//*180/3.141;
    //std::cout << "ObjectLoc " << point_vector.x << " " << point_vector.y << std::endl;

    float angle = cos((FOV+20)*(180/3.141));//
    //angle = cos(3.14/2);

    //std::cout << "Dot: " << dot_product << " Rotation: " << angle << std::endl;
    bool inside_cone = dot_product > angle;// + v*3.141/180;
    if(!inside_cone){
        //std::cout << "Dot: " << dot_product << " Rotation: " << v << std::endl;
        //std::cout << "hidden " << std::endl;
    }
    return inside_cone;
}

bool inRange(float low, float high, float x){
    return ((x-high)*(x-low) <= 0);
}
