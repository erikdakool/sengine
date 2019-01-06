//
// Created by erik on 06.01.19.
//

#ifndef GAMEPRO_ASSETMANAGER_H
#define GAMEPRO_ASSETMANAGER_H

#include <string>
#include <memory>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AssetController {
public:
    AssetController(){}
    ~AssetController(){}
    void loadTexture(std::string name, std::string url);
    std::shared_ptr<sf::Texture> getTexture(std::string name);

    void loadSoundbuffer(std::string name, std::string url);
    std::shared_ptr<sf::SoundBuffer> getSoundbuffer(std::string name);

private:
    std::map<std::string, std::shared_ptr<sf::Texture>> textures;
    std::map<std::string, std::shared_ptr<sf::SoundBuffer>> soundbuffers;
};


#endif //GAMEPRO_ASSETMANAGER_H
