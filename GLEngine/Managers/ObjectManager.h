//
// Created by erik on 23.10.2019.
//

#ifndef GLENGINE_OBJECTMANAGER_H
#define GLENGINE_OBJECTMANAGER_H

#include <memory>
#include <vector>

class Gameobject;
class Object;
class ObjectManager {
public:
    ObjectManager();
    ~ObjectManager();
    void AddObject(std::shared_ptr<Gameobject> object);

    void UpdateAll(float deltaT);
private:
    std::vector<std::shared_ptr<Gameobject>> objects;
};


#endif //GLENGINE_OBJECTMANAGER_H
