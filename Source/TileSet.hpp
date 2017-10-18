#pragma once

#include "Tile.hpp"

struct TileSet
{
    TileSet(const char* tsxFilepath);
    int tileSize; //only square tiles
    int width;
    int height;
    sf::Sprite sprite;
    std::vector<Tile> tiles;
};

