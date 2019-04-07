//
// Created by erik on 22.12.18.
//

#ifndef GAMEPRO_COMPONENT_H
#define GAMEPRO_COMPONENT_H

#include <string>

#include <jsoncpp/json/json.h>

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
    Component(Gameobject& gameobject, Json::Value input);
    ~Component();

    virtual void init();
    virtual void update(float deltaT);
    virtual Json::Value getJson();
    virtual void setValuesJson(Json::Value input);
    Json::Value getCJson();
    Gameobject &getGameobject() const;

    bool isDestroy() const;

    void setDestroy(bool destroy);

    bool isActive() const;

    void setActive(bool active);

    unsigned int getId() const;

    void setId(unsigned int id);

protected:
    //Component data
    Gameobject& gameobject;
    unsigned int id = 0;
    bool destroy = false;
    bool active = true;
};


#endif //GAMEPRO_COMPONENT_H