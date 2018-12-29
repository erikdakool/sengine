//
// Created by erik on 27.12.18.
//

#ifndef GAMEPRO_OBJECTCONTROLLER_H
#define GAMEPRO_OBJECTCONTROLLER_H

#include <list>
#include <memory>

struct RenderData;
struct ObjectData;
class Gameobject;
class ObjectController {
public:
    friend class App;
    ObjectController();
    ~ObjectController();

    void update(float deltaT);

    void spawnPlayer();

    void addObject(std::shared_ptr<Gameobject> object);
    void clearInactive();
private:
    ObjectData* objectData;
    RenderData* renderData;
    std::shared_ptr<Gameobject> player;
    std::list<std::shared_ptr<Gameobject>> objects;
    std::list<std::shared_ptr<Gameobject>> inactiveObjects;
};

#endif //GAMEPRO_OBJECTCONTROLLER_H
