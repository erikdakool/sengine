//
// Created by erik on 01.04.19.
//

#include "GraphicsController.h"

GraphicsController::GraphicsController() {

}

GraphicsController::~GraphicsController() {

}

void GraphicsController::draw() {
    for(auto i = renderers.begin(); i != renderers.end();i++) {
        i->get()->draw();
    }
}

void GraphicsController::addRenderer(std::shared_ptr<RenderCom> renderer) {
    renderers.push_back(renderer);
}

void GraphicsController::removeRenderer() {
    for(auto i = renderers.begin(); i != renderers.end();i++){
        if(i->get()->isDestroy()){
            i = renderers.erase(i);
            i--;
        }
    }
}
