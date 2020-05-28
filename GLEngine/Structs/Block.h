//
// Created by erikdesk on 5/28/20.
//

#ifndef GLENGINE_BLOCK_H
#define GLENGINE_BLOCK_H

#include <vector>
#include <string>

#include <glm/glm.hpp>

struct Block{
    glm::vec3 Location;
    std::vector<glm::vec3> Quad;
    uint64_t TextureId;
    uint64_t Id;
    uint64_t ChunkId;
};

#endif //GLENGINE_BLOCK_H
