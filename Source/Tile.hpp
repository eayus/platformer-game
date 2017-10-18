#pragma once

#include <SFML/Graphics.hpp>

enum class TileType
{
    Empty,
    Solid,
    RightSlope,
    LeftSlope
};

struct Tile
{
    Tile(sf::IntRect textureRectangle, TileType tileType); 
    sf::IntRect textureRect;
    TileType type;
};
