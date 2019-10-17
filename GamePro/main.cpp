#include <iostream>

#include "App.h"
#include "Controllers/ObjectLoader.h"

#include <TGUI/TGUI.hpp>

int main()
{
    ObjectLoader objectStreamer;
    App app;
    app.run();
    return 0;
}