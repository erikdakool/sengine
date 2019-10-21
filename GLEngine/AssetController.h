//
// Created by erik on 20.10.2019.
//

#ifndef GLENGINE_ASSETCONTROLLER_H
#define GLENGINE_ASSETCONTROLLER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <utility>
#include <vector>

struct Texture{
    Texture(std::string name, GLuint TextureId){
        this->name = std::move(name);
        this->TextureId = TextureId;
        users =0;
    }
    std::string name;
    GLuint TextureId;
    unsigned int users;
};

class AssetController {
public:
    AssetController();
    ~AssetController();
    GLuint loadBMPTexture(const std::string& name,const std::string& url);
    GLuint loadDDS( std::string name, std::string url);
    GLuint getTextureID( const std::string& name);

private:
    std::vector<Texture> Textures;
};

#endif //GLENGINE_ASSETCONTROLLER_H
