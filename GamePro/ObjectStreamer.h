//
// Created by erik on 06.01.19.
//

#ifndef GAMEPRO_OBJECTSTREAMER_H
#define GAMEPRO_OBJECTSTREAMER_H

#include <iostream>
#include <fstream>

#include <jsoncpp/json/json.h>

struct Manager;
class ObjectStreamer {
    friend class App;

public:
    ObjectStreamer();
    ~ObjectStreamer(){}

    bool loadScene();
    bool writeScene();
private:
    Manager* manager;
    void output(const Json::Value & value);
    void loadTransform(const Json::Value& value);
    void loadRenderCom(const Json::Value& value);
    void loadCollider(const Json::Value& value);
};


#endif //GAMEPRO_OBJECTSTREAMER_H
