//
// Created by erik on 06.01.19.
//

#ifndef GAMEPRO_ASSETMANAGER_H
#define GAMEPRO_ASSETMANAGER_H

#include <string>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct Texture{
    std::string name;
    std::string url;
    std::shared_ptr<sf::Texture> tex;
};

struct Sound{
    std::string name;
    std::string url;
    std::shared_ptr<sf::SoundBuffer> sb;
};

class AssetController {
public:
    AssetController(){}
    ~AssetController(){}

    void loadTexture(std::string name, std::string url);
    std::shared_ptr<sf::Texture> getTexture(std::string name);
    Texture getTextureStruct(std::shared_ptr<sf::Texture> tex);

    void loadSoundbuffer(std::string name, std::string url);
    std::shared_ptr<sf::SoundBuffer> getSoundbuffer(std::string name);
    Sound getSoundStruct(std::shared_ptr<sf::SoundBuffer> sb);

private:
    std::vector<Texture> textures;
    std::vector<Sound> sounds;
};


#endif //GAMEPRO_ASSETMANAGER_H
