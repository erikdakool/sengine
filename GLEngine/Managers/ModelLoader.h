//
// Created by erik on 22.10.2019.
//

#ifndef GLENGINE_MODELLOADER_H
#define GLENGINE_MODELLOADER_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <map>
#include <memory>

struct ModelStruct{
    std::vector< glm::vec3> vertices;
    std::vector< glm::vec2> uvs;
    std::vector< glm::vec3> normals;
    unsigned int Users = 0;
};

class ModelLoader {
public:
    ModelLoader();
    ~ModelLoader();
    std::shared_ptr<ModelStruct> LoadOBJ(std::string name, std::string url);
    std::shared_ptr<ModelStruct> GetOBJ(std::string name);

private:
    std::map<std::string,std::shared_ptr<ModelStruct>> models;
};

#endif //GLENGINE_MODELLOADER_H