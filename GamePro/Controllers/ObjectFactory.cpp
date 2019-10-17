//
// Created by erik on 03.04.19.
//

#include "ObjectFactory.h"
#include "../Gameobjects/Gameobject.h"
#include "../Components/AnimationController.h"
#include "../Components/AudioCom.h"
#include "../Components/Movement.h"
#include "../Components/Physics.h"
#include "../Components/PlayerController.h"

ObjectFactory::ObjectFactory() {

}

ObjectFactory::~ObjectFactory() {

}

std::shared_ptr<Gameobject> ObjectFactory::createGameobject() {
    auto ob = std::make_shared<Gameobject>(*manager);
    ob->id = this->id;
    this->id ++;
    return ob;
}

std::shared_ptr<Gameobject> ObjectFactory::createGameobject(Json::Value input) {
    auto ob = std::make_shared<Gameobject>(*manager);

    for(Json::Value& component: input["components"]){
        if(component["name"].asString()=="transform"){
            auto com = std::make_shared<Transform>(*ob.get(),component);
            ob.get()->addComponent(com);
            ob.get()->transform = com;
        }if(component["name"].asString()=="animationController"){
            auto com = std::make_shared<AnimationController>(*ob.get(),component);
            ob.get()->addComponent(com);
        }
        if(component["name"].asString()=="audioCom"){
            auto com = std::make_shared<AudioCom>(*ob.get(),component);
            ob.get()->addComponent(com);
        }
        if(component["name"].asString()=="collider"){
            auto col = std::make_shared<Collider>(*ob.get(),component);
            manager->collisionController.addCollider(col);
            ob.get()->addComponent(col);
        }
        if(component["name"].asString()=="movement"){
            auto com = std::make_shared<Movement>(*ob.get(),component);
            ob.get()->addComponent(com);
        }
        if(component["name"].asString()=="physics"){
            auto com = std::make_shared<Physics>(*ob.get(),component);
            ob.get()->addComponent(com);
        }
        if(component["name"].asString()=="playercontroller"){
            auto com = std::make_shared<PlayerController>(*ob.get(),component);
            ob.get()->addComponent(com);
        }
        if(component["name"].asString()=="rendercom"){
            auto com = std::make_shared<RenderCom>(*ob.get(),component);
            ob.get()->addComponent(com);
        }
    }

    ob.get()->id = input["id"].asUInt();
    ob.get()->active = input["active"].asBool();
    ob.get()->name = input["name"].asString();
    ob.get()->tag = static_cast<ObjectTag >(input["tag"].asInt());
    return ob;
}
