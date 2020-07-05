//
// Created by erikdesk on 5/28/20.
//

#ifndef GLENGINE_CHUNKMANAGER_H
#define GLENGINE_CHUNKMANAGER_H

#include "../Object/Block.h"
#include "../Managers.h"
#include "../Structs/BlockInfo.h"
#include "../Structs/TextureInfo.h"

#define CHUNKSIZE 8
static int chunkSize = CHUNKSIZE;

class TerrainGenerator;
class ChunkManager {
public:
    ChunkManager(GameDataRef data, TerrainGenerator& terrainGenerator, int x, int y, int z);
    ~ChunkManager();

    void Update();
    void Draw();
    uint64_t AddBlock(int x, int y, int z, int chunkXoffset, int chunkYoffset,int type);
    void RemoveBlock(uint64_t id);
    void ClearBlocks();
    void calculateSides();
private:
    GameDataRef _data;
    TerrainGenerator& terrainGenerator;

    void updateBuffer();
    std::shared_ptr<Block> getBlock(int x, int y, int z);
    bool getBlockExists(int x, int y, int z);

    std::vector<BlockInfo> blockInfo;
    std::vector<TextureInfo> textureInfo;

    std::vector<std::shared_ptr<Block>> blocks;

    std::map<std::tuple<int,int,int>,std::shared_ptr<Block>> ChunkBlocks;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    uint64_t idCounter = 0;

    GLuint vertexArrayID;
    GLuint vertexBufferID;
    GLuint indiceBufferID;

    GLuint indiceCounter = 0;

    int texturesCount = 5;
    std::vector<GLuint> textures;

    std::tuple<int,int,int> chunkLoc;
};

#endif //GLENGINE_CHUNKMANAGER_H


