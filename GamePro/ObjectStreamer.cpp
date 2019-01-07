//
// Created by erik on 06.01.19.
//

#include "ObjectStreamer.h"
#include "Manager.h"

ObjectStreamer::ObjectStreamer() {

}

bool ObjectStreamer::writeScene() {
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

bool ObjectStreamer::loadScene() {
    Json::Value scene;
    Json::Reader reader;

    std::ifstream file;
    file.open("Data/file.json");

    bool parsing = reader.parse(file,scene);
    if(!parsing)
        return false;


}

void ObjectStreamer::output(const Json::Value &value) {
    // querying the json object is very simple
    std::cout << value["hello"];
    std::cout << value["number"];
    std::cout << value["array"][0] << value["array"][1];
    std::cout << value["object"]["hello"];
}