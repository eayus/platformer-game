#include "ResourceManager.hpp"

#include "Utils/Logging.hpp"

std::unordered_map<std::string, std::unique_ptr<sf::Texture>> ResourceManager::m_textureMap;

sf::Texture* ResourceManager::getTexture(const std::string& filepath) {

    auto it = m_textureMap.find(filepath);

    if (it != m_textureMap.end())
        return it->second.get();
    else {
        auto texture = std::make_unique<sf::Texture>();
        if (!texture->loadFromFile(filepath)) {
            Utils::log("[ERROR]: cannot find the following texture:");
            Utils::log(filepath);
        }

        it = m_textureMap.insert(std::make_pair(filepath, std::move(texture))).first;

        return it->second.get();

    }

}
