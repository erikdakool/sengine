//
// Created by erik on 27.12.18.
//

#ifndef GAMEPRO_OBJECTCONTROLLER_H
#define GAMEPRO_OBJECTCONTROLLER_H

#include <list>
#include <memory>

class Gameobject;
class ObjectController {
public:
    ObjectController();
    ~ObjectController();

    void update(float deltaT);
    void draw();

    void addObject(std::shared_ptr<Gameobject> object);
    void clearInactive();
private:
    std::list<std::shared_ptr<Gameobject>> objects;
    std::list<std::shared_ptr<Gameobject>> inactiveObjects;
};

#endif //GAMEPRO_OBJECTCONTROLLER_H
