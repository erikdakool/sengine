//
// Created by erik on 06.01.19.
//

#include "ObjectLoader.h"
#include "../Manager.h"
#include "../Gameobjects/Gameobject.h"

ObjectLoader::ObjectLoader() {

}

bool ObjectLoader::writeScene() {
    std::ofstream file;
    file.open("Data/file.json");

    Json::Value scene;
    scene["gameobjects"] = manager->objectController.getJson();

    Json::StyledWriter styledWriter;
    //std::cout << styledWriter.write(scene);
    file << styledWriter.write(scene);

    Json::FastWriter fastWriter;
    //file << fastWriter.write(scene);
    file.close();
}

bool ObjectLoader::loadScene() {
    Json::Value scene;
    Json::Reader reader;

    std::ifstream file;
    file.open("Data/file.json");

    bool parsing = reader.parse(file,scene);
    if(!parsing)
        return false;

    for(Json::Value& object: scene["gameobjects"]){
        auto ob = manager->objectFactory.createGameobject(object);
        if(ob.get()->getTag() == TagPlayer)
            manager->objectController.addPlayer(ob);

        manager->objectController.addObject(ob);
    }
    manager->objectController.initAll();
}
