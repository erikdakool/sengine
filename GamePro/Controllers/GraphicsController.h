//
// Created by erik on 01.04.19.
//

#ifndef GAMEPRO_GRAPHICSCONTROLLER_H
#define GAMEPRO_GRAPHICSCONTROLLER_H

#include <memory>
#include <list>

#include "../Components/RenderCom.h"
#include "WindowController.h"

class GraphicsController {
public:
    GraphicsController();
    ~GraphicsController();

    void draw();

    void addRenderer(std::shared_ptr<RenderCom> renderer);
    void removeRenderer();

private:
    std::list<std::shared_ptr<RenderCom>> renderers;
};


#endif //GAMEPRO_GRAPHICSCONTROLLER_H
