//
// Created by erik on 21.10.2019.
//

#ifndef GLENGINE_VBOINDEX_H
#define GLENGINE_VBOINDEX_H

#include <glm/fwd.hpp>
#include <vector>

void indexVBO(
    std::vector<glm::vec3> & in_vertices,
    std::vector<glm::vec2> & in_uvs,

    std::vector<unsigned short> & out_indices,
    std::vector<glm::vec3> & out_vertices,
    std::vector<glm::vec2> & out_uvs
);

#endif //GLENGINE_VBOINDEX_H