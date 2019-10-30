//
// Created by erik on 23.10.2019.
//

#ifndef GLENGINE_OBJECT_H
#define GLENGINE_OBJECT_H


#include "../Managers.h"

class Object {
public:
    Object(GameDataRef data);
    ~Object();

    unsigned int getId() const;
    virtual void update(float deltaT) = 0;
    //virtual void init() = 0;
private:

protected:
    GameDataRef _data;
    unsigned int id = 0;
    bool active = true;
};

#endif //GLENGINE_OBJECT_H
