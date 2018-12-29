//
// Created by erik on 22.12.18.
//

#ifndef GAMEPRO_COMPONENT_H
#define GAMEPRO_COMPONENT_H

#include <string>


enum Dir{
    Right,
    Left,
    Up,
    Down
};

class Gameobject;
class Component {
public:
    Component(Gameobject& gameobject);
    ~Component();

    virtual void init();
    virtual void update(float deltaT);
    Gameobject &getGameobject() const;


    bool isDestroy() const;

    void setDestroy(bool destroy);

    bool isActive() const;

    void setActive(bool active);

    unsigned int getId() const;

    void setId(unsigned int id);

private:
    //Component data
    Gameobject& gameobject;
    unsigned int id;
    std::string name;
    bool destroy = false;
    bool active = true;
};


#endif //GAMEPRO_COMPONENT_H