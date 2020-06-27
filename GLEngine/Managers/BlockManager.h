//
// Created by erikdesk on 5/28/20.
//

#ifndef GLENGINE_BLOCKMANAGER_H
#define GLENGINE_BLOCKMANAGER_H

#include "../Object/Block.h"
#include "../Managers.h"
#include "../Structs/BlockInfo.h"
#include "../Structs/TextureInfo.h"

class BlockManager {
public:
    BlockManager(GameDataRef data);
    ~BlockManager();

    void Update();
    void Draw();
    uint64_t AddBlock(glm::vec3 location, std::string textureId, uint64_t chunk, int type);
    void RemoveBlock(uint64_t id);
    void ClearBlocks();
private:
    GameDataRef _data;

    void updateBuffer();

    std::vector<BlockInfo> blockInfo;
    std::vector<TextureInfo> textureInfo;

    std::vector<Block> blocks;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    uint64_t idCounter = 0;

    GLuint vertexArrayID;
    GLuint vertexBufferID;
    GLuint indiceBufferID;

    GLuint indiceCounter = 0;

    int texturesCount = 4;
    std::vector<GLuint> textures;
};

#endif //GLENGINE_BLOCKMANAGER_H


