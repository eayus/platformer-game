#pragma once

#include <SFML/Graphics.hpp>
#include "AABB.hpp"

class Level;

class GameObject
{
public:
    GameObject(sf::Vector2i position, AABB aabb, Level* level);
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update() = 0;
    AABB getBoundingBox() const;
    bool shouldDelete() const;
	void setDelete();
	virtual void collided(GameObject* other) = 0;

protected:
    sf::Vector2i m_position;
    AABB m_aabb; //This is the collision box RELATIVE to the position of the object.
    Level* m_level;
    bool m_shouldDelete;
    
};
