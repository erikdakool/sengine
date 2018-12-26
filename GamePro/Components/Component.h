//
// Created by erik on 22.12.18.
//

#ifndef GAMEPRO_COMPONENT_H
#define GAMEPRO_COMPONENT_H

class Gameobject;
class Component {
public:
    Component(Gameobject& gameobject);
    ~Component();

    virtual void init();
    virtual void update(float deltaT);

    Gameobject &getGameobject() const;
private:
    Gameobject& gameobject;
    bool active;
};


#endif //GAMEPRO_COMPONENT_H