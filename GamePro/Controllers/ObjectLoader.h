//
// Created by erik on 06.01.19.
//

#ifndef GAMEPRO_OBJECTSTREAMER_H
#define GAMEPRO_OBJECTSTREAMER_H

#include <iostream>
#include <fstream>

#include <json/json.h>
struct Manager;
class ObjectLoader {
    friend class App;

public:
    ObjectLoader();
    ~ObjectLoader(){}

    bool loadScene();
    bool writeScene();
private:
    Manager* manager;

    void loadTransform(const Json::Value& value);
    void loadRenderCom(const Json::Value& value);
    void loadCollider(const Json::Value& value);
};


#endif //GAMEPRO_OBJECTSTREAMER_H
