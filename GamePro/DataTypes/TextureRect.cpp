//
// Created by erik on 23.03.19.
//

#include "TextureRect.h"

TextureRect::TextureRect(std::shared_ptr<sf::Texture> tex) {
    auto rect = std::make_shared<sf::IntRect>();
    intRect = rect;

    texture = tex;
}

TextureRect::TextureRect(std::shared_ptr<sf::Texture> tex, int x, int y, int width, int height) {
    auto rect = std::make_shared<sf::IntRect>(x,y,width,height);
    intRect = rect;

    texture = tex;
}

TextureRect::TextureRect(Json::Value input, AssetController assetController) {
    int x = input["x"].asInt();
    int y = input["y"].asInt();
    int width = input["width"].asInt();
    int height = input["height"].asInt();
    auto rect = std::make_shared<sf::IntRect>(x,y,width,height);
    intRect = rect;

    std::string url = input["url"].asString();
    std::string texName = input["textureName"].asString();
    assetController.loadTexture(texName,url);
    auto tex = assetController.getTexture(texName);
    this->texture = tex;
}

TextureRect::~TextureRect() {

}

Json::Value TextureRect::getJson(AssetController assetController) {
    Json::Value ret;
    ret["name"] = "textureRect";
    ret["x"] = intRect.get()->left;
    ret["y"] = intRect.get()->top;
    ret["width"] = intRect.get()->width;
    ret["height"] = intRect.get()->height;
    Texture tex = assetController.getTextureStruct(this->texture);
    ret["textureName"] = tex.name;
    ret["url"] = tex.url;
    return ret;
}
