//
// Created by erik on 23.03.19.
//

#ifndef GAMEPRO_INPUTCONTROLLER_H
#define GAMEPRO_INPUTCONTROLLER_H

#include <SFML/Window/Joystick.hpp>
#include <SFML/Window.hpp>
#include <jsoncpp/json/json.h>

struct Input{
    std::string name;
    sf::Keyboard keyboard;
    sf::Joystick joystickButton;
    sf::Joystick::Axis joystickAxis;
    bool pressed = false;
};

class InputController {
public:
    InputController();
    bool loadInputs();
    bool writeInputs();

    bool buttonPressed(std::string);
    float getAxis();

private:
    Input inputs[0];
};

#endif //GAMEPRO_INPUTCONTROLLER_H