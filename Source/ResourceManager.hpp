#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

class ResourceManager
{
public:
    static sf::Texture* getTexture(const std::string& filepath);
    static std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textureMap;

private:
    ResourceManager() {};

};
