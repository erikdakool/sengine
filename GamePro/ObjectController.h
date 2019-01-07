//
// Created by erik on 27.12.18.
//

#ifndef GAMEPRO_OBJECTCONTROLLER_H
#define GAMEPRO_OBJECTCONTROLLER_H

#include <list>
#include <memory>

#include <jsoncpp/json/json.h>

struct Manager;
class Gameobject;
class ObjectController {
public:
    friend class App;
    ObjectController();
    ~ObjectController();

    void update(float deltaT);
    Json::Value getJson();
    void spawnPlayer();

    void addObject(std::shared_ptr<Gameobject> object);
    void clearInactive();
private:
    Manager* manager;
    std::shared_ptr<Gameobject> player;
    std::list<std::shared_ptr<Gameobject>> objects;
    std::list<std::shared_ptr<Gameobject>> inactiveObjects;
};

#endif //GAMEPRO_OBJECTCONTROLLER_H
