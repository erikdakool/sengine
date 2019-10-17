//
// Created by erik on 29.12.18.
//

#include <iostream>
#include <cmath>

#include "Physics.h"
#include "../Gameobjects/Gameobject.h"
#include "Collider.h"
#include "../SceneVariables.h"

Physics::Physics(Gameobject &gameobject)
:Component(gameobject)
{

}

Physics::Physics(Gameobject &gameobject, Json::Value input)
:Component(gameobject)
{
    Physics::setValuesJson(input);

}

Physics::~Physics() {

}

void Physics::init() {
    PhysicConstants pc;
    cyAcc = pc.yAcc;
    cxAcc = pc.xAcc;
    col = getGameobject().getComponentP<Collider*>();
}

Json::Value Physics::getJson() {
    Json::Value ret = Component::getCJson();
    ret["name"] = "physics";
    return ret;
}

void Physics::setValuesJson(Json::Value input) {
    Component::setValuesJson(input);
}

void Physics::update(float deltaT) {
    deltaT = deltaT*10;

    //check gravity applicable
    auto obj = getGameobject().getManager().collisionController.checkCollision(*col,Down,.1f);
    if(obj)
    {
        cyAcc = 0;
    } else{
        cyAcc = 0; //9.81f;
    }

    //Resistance force calculated
    float yrFor = 0;//dragCo * (yVel*yVel);
    float xrFor = 0;//dragCo * (xVel*xVel);

    //total force for tick calculated
    yFor = (cyAcc* mass * deltaT)-yrFor + yImp;
    xFor = (cxAcc* mass * deltaT)-xrFor + xImp;

    bool xHit = false;
    bool yHit = false;
    //ypos change
    float yPosD = yVel * deltaT +(0.5f*lyAcc*(deltaT*deltaT));
    if(yPosD>0){
        getGameobject().trasform()->increaseY(yPosD);
        auto t = getGameobject().getManager().collisionController.collision(*getGameobject().getComponentP<Collider*>());
        if(t){
            auto phys = t->getGameobject().getComponentP<Physics*>();
            if(phys){
                phys->addVel(Down,this->mass*fabsf(yVel));
            }
            getGameobject().trasform()->setY(t->getGameobject().trasform()->getY()+t->getYOff()-col->getHeight());
            yHit = true;
        }
    } else if(yPosD!=0){
        getGameobject().trasform()->increaseY(yPosD);
        auto t = getGameobject().getManager().collisionController.collision(*getGameobject().getComponentP<Collider*>());
        if(t){
            auto phys = t->getGameobject().getComponentP<Physics*>();
            if(phys){
                phys->addVel(Up,this->mass*fabsf(yVel));
            }
            getGameobject().trasform()->setY(t->getGameobject().trasform()->getY()+t->getYOff()+t->getHeight());
            yHit = true;
        }
    }
    float yAcc = yFor/mass;
    float avyAcc = (lyAcc + yAcc)/2;
    yVel += avyAcc * deltaT;
    lyAcc = yAcc;

    //xpos change
    float xPosD = xVel * deltaT +(0.5f*lxAcc*(deltaT*deltaT));
    if(xPosD>0){
        getGameobject().trasform()->increaseX(xPosD);
        auto t = getGameobject().getManager().collisionController.collision(*getGameobject().getComponentP<Collider*>());
        if(t){
            auto phys = t->getGameobject().getComponentP<Physics*>();
            if(phys){
                phys->addVel(Right,this->mass*fabsf(xVel));
            }
            getGameobject().trasform()->setX(t->getGameobject().trasform()->getX()+t->getXOff()-col->getWidth());
            xHit = true;
        }
    } else if (xPosD!=0){
        getGameobject().trasform()->increaseX(xPosD);
        auto t = getGameobject().getManager().collisionController.collision(*getGameobject().getComponentP<Collider*>());
        if(t){
            auto phys = t->getGameobject().getComponentP<Physics*>();
            if(phys){
                phys->addVel(Left,this->mass*fabsf(xVel));
            }
            getGameobject().trasform()->setX(t->getGameobject().trasform()->getX()+t->getXOff()+t->getWidth());
            xHit = true;
        }
    }
    float xAcc = xFor/mass;
    float avxAcc = (lxAcc + xAcc)/2;
    xVel += avxAcc * deltaT;
    lxAcc = xAcc;

    if(yHit){
        lyAcc = 0;
        yVel = 0;
        yImp = 0;
    }

    if(xHit){
        lxAcc = 0;
        xVel = 0;
        xImp = 0;
    }
    //std::cout << xFor << "      " << xImp << "      " << xVel << "     " << xrFor <<    std::endl;
    //std::cout << yFor << "      " << yImp << "      " << yVel << "     " << yrFor <<    std::endl;
    xImp = 0;
    yImp = 0;
    //std::cout <<getGameobject().trasform()->getY() << "     " <<  yPosD << "    " << yVel << "     " << yAcc << "      " << yFor << std::endl;
}

void Physics::addFor(Dir dir, float value) {
    switch (dir){
        case Right:
            xImp +=value;
            break;
        case Left:
            xImp-= value;
            break;
        case Up:
            yImp -= value;
            break;
        case Down:
            yImp += value;
            break;
    }
}

void Physics::addVel(Dir dir, float value) {
    switch (dir){
        case Right:
            xVel +=value/mass;
            break;
        case Left:
            xVel-= value/mass;
            break;
        case Up:
            yVel -= value/mass;
            break;
        case Down:
            yVel += value/mass;
            break;
    }
}

float Physics::getXVel() const {
    return xVel;
}

float Physics::getYVel() const {
    return yVel;
}
