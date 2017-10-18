#include "GameObject.hpp"
#include "Level.hpp"

GameObject::GameObject(const sf::Vector2i& position, const AABB& aabb, Level* level):
    m_position(position),
    m_aabb(aabb),
    m_level(level),
    m_shouldDelete(false) {

}

AABB GameObject::getBoundingBox() {

    AABB box = m_aabb;

    box.x += m_position.x;
    box.y += m_position.y;

    return box;

}

bool GameObject::shouldDelete() {

    return m_shouldDelete;

}
