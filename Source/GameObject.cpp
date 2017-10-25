#include "GameObject.hpp"
#include "Level.hpp"

GameObject::GameObject(sf::Vector2i position, AABB aabb, Level* level):
    m_position(position),
    m_aabb(aabb),
    m_level(level),
    m_shouldDelete(false) {

}

AABB GameObject::getBoundingBox() const {

    AABB box = m_aabb;

    box.x += m_position.x;
    box.y += m_position.y;

    return box;

}

bool GameObject::shouldDelete() const {

    return m_shouldDelete;

}

void GameObject::setDelete() {

	m_shouldDelete = true;

}
