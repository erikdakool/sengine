//
// Created by erik on 20.10.2019.
//

#ifndef GLENGINE_TEXTURELOADER_H
#define GLENGINE_TEXTURELOADER_H

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

class TextureLoader {
public:
    TextureLoader();
    ~TextureLoader();
    GLuint loadBMPTexture(const std::string& name,const std::string& url);
    GLuint loadBMPTexture(const std::string& name,const std::string& url,const int tileX, int tileY, const int tileW, const int tileH,int unit);
    GLuint loadDDS( std::string name, std::string url);
    GLuint getTextureID( const std::string& name);

private:
    std::vector<Texture> Textures;
};

#endif //GLENGINE_TEXTURELOADER_H
