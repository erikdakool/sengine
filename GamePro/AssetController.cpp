//
// Created by erik on 06.01.19.
//

#include <iostream>
#include "AssetController.h"

void AssetController::loadTexture(std::string name, std::string url) {
    for (int i = 0; i < textures.size(); ++i) {
        if(textures.at(i).name == name){
            return;
        }
    }
    auto tex = std::make_shared<sf::Texture>();
    tex->loadFromFile(url);

    Texture texS;
    texS.name = name;
    texS.url = url;
    texS.tex = tex;
    textures.push_back(texS);
    std::cout << "loaded texture" << std::endl;
}

std::shared_ptr<sf::Texture> AssetController::getTexture(std::string name) {
    for (int i = 0; i < textures.size(); ++i) {
        if(textures.at(i).name == name){
            return textures.at(i).tex;
        }
    }
    return nullptr;
}

Texture AssetController::getTextureStruct(std::shared_ptr<sf::Texture> tex) {
    for (int i = 0; i < textures.size(); ++i) {
        if(textures.at(i).tex == tex){
            return textures.at(i);
        }
    }
}

void AssetController::loadSoundbuffer(std::string name, std::string url) {
    for (int i = 0; i < sounds.size(); ++i) {
        if(sounds.at(i).name == name){
            return;
        }
    }
    auto sb = std::make_shared<sf::SoundBuffer>();
    sb->loadFromFile(url);

    Sound sbS;
    sbS.name = name;
    sbS.url = url;
    sbS.sb = sb;
    sounds.push_back(sbS);
}

std::shared_ptr<sf::SoundBuffer> AssetController::getSoundbuffer(std::string name) {
    for (int i = 0; i < sounds.size(); ++i) {
        if(sounds.at(i).name == name){
            return sounds.at(i).sb;
        }
    }
    return nullptr;
}

Sound AssetController::getSoundStruct(std::shared_ptr<sf::SoundBuffer> sb) {
    for (int i = 0; i < sounds.size(); ++i) {
        if(sounds.at(i).sb == sb){
            return sounds.at(i);
        }
    }
}