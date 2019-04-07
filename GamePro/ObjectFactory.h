//
// Created by erik on 03.04.19.
//

#ifndef GAMEPRO_OBJECTFACTORY_H
#define GAMEPRO_OBJECTFACTORY_H

#include <memory>

#include <jsoncpp/json/json.h>

struct Manager;
class Gameobject;
class ObjectFactory {
public:
    friend class App;
    ObjectFactory();
    ~ObjectFactory();

    std::shared_ptr<Gameobject> createGameobject();
    std::shared_ptr<Gameobject> createGameobject(Json::Value input);

private:
    Manager* manager;
    unsigned int id;
};


#endif //GAMEPRO_OBJECTFACTORY_H
