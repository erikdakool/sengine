//
// Created by erik on 23.03.19.
//

#include <fstream>
#include "InputController.h"

InputController::InputController()
{
    writeInputs();
    loadInputs();
}

bool InputController::writeInputs(){
    std::string url = "Data/input.json";

    std::ofstream file;
    file.open(url);

    Json::Value inputs;

    inputs["inputs"]["forward"]["name"] = "forward";
    inputs["inputs"]["forward"]["keyboard"] = sf::Keyboard::W;
    inputs["inputs"]["forward"]["controllerAxis"] = sf::Joystick::Y;
    inputs["inputs"]["forward"]["controllerButton"] = 0;

    Json::StyledWriter styledWriter;
    file << styledWriter.write(inputs);
    file.close();
}

bool InputController::loadInputs() {
    Json::Value inputs;
    Json::Reader reader;

    std::ifstream file;
    std::string url = "Data/input.json";
    file.open(url);

    bool parsing = reader.parse(file,inputs);
    if(!parsing)
        return false;

    int iSize = inputs["inputs"].size();
    inputs = new Input[iSize];

/*    for(Json::Value& input: inputs["inputs"]){
        std::string name = input["name"].asString();
        if(!input["keyboard"].isNull()){
           int key = input["keyboard"].asInt();
        }
    }*/
}

bool InputController::buttonPressed(std::string) {

}

float InputController::getAxis() {

}
