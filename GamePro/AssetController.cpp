//
// Created by erik on 06.01.19.
//

#include "AssetController.h"

void AssetController::loadTexture(std::string name, std::string url) {
    if(textures.find(name)==textures.end()){
        auto tex = std::make_shared<sf::Texture>();
        tex->loadFromFile(url);
        textures[name] = tex;
    }
}

std::shared_ptr<sf::Texture> AssetController::getTexture(std::string name) {
    if(textures.find(name)!=textures.end()){
        return textures[name];
    }
    return nullptr;
}

void AssetController::loadSoundbuffer(std::string name, std::string url) {
    if(soundbuffers.find(name)==soundbuffers.end()){
        auto sb = std::make_shared<sf::SoundBuffer>();
        sb->loadFromFile(url);
        soundbuffers[name] = sb;
    }
}

std::shared_ptr<sf::SoundBuffer> AssetController::getSoundbuffer(std::string name) {
    if(soundbuffers.find(name)!=soundbuffers.end()){
        return soundbuffers[name];
    }
    return nullptr;
}