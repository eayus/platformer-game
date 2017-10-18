#pragma once

#include <SFML/Graphics.hpp>
#include "AABB.hpp"

class Level;

class GameObject
{
public:
    GameObject(const sf::Vector2i& position, const AABB& aabb, Level* level);
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update() = 0;
    AABB getBoundingBox();
    bool shouldDelete();    

protected:
    sf::Vector2i m_position;
    AABB m_aabb; //This is the collision box RELATIVE to the position of the object.
    Level* m_level;
    bool m_shouldDelete;
    
};
