//
// Created by erik on 22.10.2019.
//

#ifndef GLENGINE_MANAGERS_H
#define GLENGINE_MANAGERS_H

#include <memory>

#include "TextureLoader.h"
#include "ModelLoader.h"

struct GameData{
    Camera camera;
    TextureLoader textureLoader;
    ModelLoader modelLoader;
};
typedef std::shared_ptr<GameData> GameDataRef;

#endif //GLENGINE_MANAGERS_H
