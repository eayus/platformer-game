#include "AABB.hpp"

AABB::AABB():
    x(0),
    y(0),
    w(0),
    h(0) {

}

AABB::AABB(int xCoord, int yCoord, int width, int height):
    x(xCoord),
    y(yCoord),
    w(width),
    h(height) {

}

sf::Vector2i AABB::getCenter() {

    return sf::Vector2i(x + (w / 2), y + (h / 2));

}

bool AABB::intersects(const AABB& other) {

	return !(x + w < other.x || other.x + other.w < x || y + h < other.y || other.y + other.h < y);

}
