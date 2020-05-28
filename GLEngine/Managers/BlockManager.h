//
// Created by erikdesk on 5/28/20.
//

#ifndef GLENGINE_BLOCKMANAGER_H
#define GLENGINE_BLOCKMANAGER_H

#include "../Structs/Block.h"
#include "../Managers.h"
class BlockManager {
public:
    BlockManager(GameDataRef data);
    ~BlockManager();

    void Update();
    void Draw();
    uint64_t AddBlock(glm::vec3 locaiton, std::string textureId);
    void RemoveBlock(uint64_t id);

private:
    GameDataRef _data;

    std::map<GLuint,std::string> texturesLoaded;
    std::vector<Block> blocks;

    glm::vec3 points[36];

    uint64_t idCounter = 0;
    uint64_t chunkCounter;
};

#endif //GLENGINE_BLOCKMANAGER_H


