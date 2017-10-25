#pragma once

#include <SFML/Graphics.hpp>

struct AABB
{
    AABB();
    AABB(int xCoord, int yCoord, int width, int height);
    sf::Vector2i getCenter();
	bool intersects(const AABB& other);
    int x;
    int y;
    int w;
    int h;
};
