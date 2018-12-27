//
// Created by erik on 22.12.18.
//

#ifndef GAMEPRO_COMPONENT_H
#define GAMEPRO_COMPONENT_H

#include <string>

class Gameobject;
class Component {
public:
    Component(Gameobject& gameobject);
    ~Component();

    virtual void init();
    virtual void update(float deltaT);

    Gameobject &getGameobject() const;

    bool isActive() const;

private:
    //Component data
    Gameobject& gameobject;
    unsigned int id;
    std::string name;
    bool active = true;
};


#endif //GAMEPRO_COMPONENT_H