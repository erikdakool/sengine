//
// Created by erik on 23.10.2019.
//

#ifndef GLENGINE_OBJECTMANAGER_H
#define GLENGINE_OBJECTMANAGER_H

#include <memory>
#include <vector>
#include <list>
#include <algorithm>

class Gameobject;
class Object;
class ObjectManager {
public:
    ObjectManager();
    ~ObjectManager();
    void AddObject(std::shared_ptr<Gameobject> object);
    void RemoveObject(uint64_t id);

    void UpdateAll(float deltaT);
private:
    std::list<std::shared_ptr<Gameobject>> objects;
    uint64_t objectcount = 1;
    std::list<uint64_t> pendingRemove;
};


#endif //GLENGINE_OBJECTMANAGER_H
