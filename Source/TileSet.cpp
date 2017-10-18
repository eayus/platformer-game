#include "TileSet.hpp"
#include "ResourceManager.hpp"
#include "Utils/Logging.hpp"

#include <pugixml.hpp>
#include <cstring>
#include <iostream>

TileSet::TileSet(const char* tsxFilepath) {

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(tsxFilepath);

    Utils::log(result.description());

    tileSize = std::stoi(doc.child("tileset").attribute("tilewidth").value());

    pugi::xml_node image = doc.child("tileset").child("image");

    width = std::stoi(image.attribute("width").value());
    height = std::stoi(image.attribute("height").value());

    std::string textureFilepath = "Maps/";
    textureFilepath += image.attribute("source").value();
    sf::Texture* tex = ResourceManager::getTexture(textureFilepath);

    sprite.setTexture(*tex);

    int x = 0;
    int y = 0;

    for (pugi::xml_node tile = doc.child("tileset").child("tile"); tile; tile = tile.next_sibling("tile")) {

        TileType tiletype;

        const char* typeString = tile.attribute("type").value();

        if (strcmp(typeString, "Empty") == 0)
            tiletype = TileType::Empty;
        else if (strcmp(typeString, "Solid") == 0)
            tiletype = TileType::Solid;
        else if (strcmp(typeString, "RightSlope") == 0)
            tiletype = TileType::RightSlope;
        else if (strcmp(typeString, "LeftSlope") == 0)
            tiletype = TileType::LeftSlope;
        else {
            tiletype = TileType::Empty;
            Utils::log("[ERROR]: invadid tile type!");
        }

        tiles.push_back(Tile(sf::IntRect(x, y, tileSize, tileSize), tiletype));

        x += tileSize;

        if (x >= width) {
            y += tileSize;
            x = 0;
        }

    }


}
