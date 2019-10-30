//
// Created by erik on 22.10.2019.
//

#ifndef GLENGINE_MANAGERS_H
#define GLENGINE_MANAGERS_H

#include <memory>

#include "Managers/TextureLoader.h"
#include "Managers/ModelLoader.h"
#include "Managers/ObjectManager.h"
#include "CollisionManager.h"
#include "Camera.h"

struct GameData{
    Camera camera;
    TextureLoader textureLoader;
    ModelLoader modelLoader;
    ObjectManager objectManager;
    CollisionManager collisionManager;
};
typedef std::shared_ptr<GameData> GameDataRef;

#endif //GLENGINE_MANAGERS_H
