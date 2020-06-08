//
// Created by erikdesk on 5/28/20.
//

#ifndef GLENGINE_BLOCKMANAGER_H
#define GLENGINE_BLOCKMANAGER_H

#include "../Object/Block.h"
#include "../Managers.h"

class BlockManager {
public:
    BlockManager(GameDataRef data);
    ~BlockManager();

    void Update();
    void Draw();
    uint64_t AddBlock(glm::vec3 locaiton, std::string textureId, uint64_t chunk,BlockType type);
    void RemoveBlock(uint64_t id);
    void ClearBlocks();
private:
    GameDataRef _data;

    void updateBuffer();

    std::map<GLuint,std::string> texturesLoaded;
    std::vector<Block> blocks;

    std::vector<float> vertices;
    std::vector<float> vertexes;
    std::vector<unsigned int> indices;
    std::vector<float> colors;
    std::vector<float> texturePos;

    uint32_t* indicesArr;

    glm::vec3 points[36];
    glm::vec2 uvs[36];

    uint64_t idCounter = 0;

    GLuint vertexArrayID;
    GLuint vertexBufferID;
    GLuint indiceBufferID;

    GLuint indiceCounter = 0;

    GLuint grassId;
    GLuint dirtId;
    GLuint stoneId;
};

#endif //GLENGINE_BLOCKMANAGER_H


