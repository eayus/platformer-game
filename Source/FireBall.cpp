#include "FireBall.hpp"
#include "ResourceManager.hpp"
#include "Level.hpp"

FireBall::FireBall(const sf::Vector2i& position, const sf::Vector2i& velocity, Level* level):
    GameObject(position, AABB(0, 0, 16, 16), level),
    m_velocity(velocity),
    m_anim(ResourceManager::getTexture("Assets/FireBall.png"), std::vector<sf::IntRect>{ sf::IntRect(0, 0, 16, 16) }, 20) {

}

void FireBall::draw(sf::RenderWindow& window) {

    m_anim.draw(window, m_position);

}

void FireBall::update() {

    m_position += m_velocity;

    AABB box = this->getBoundingBox();

    //Add vertical checking eventually

    if (m_velocity.x > 0) {

        if (m_level->getTileTypeAtCoord(box.x + box.w, box.y) != TileType::Empty)
            m_shouldDelete = true;

        if (m_level->getTileTypeAtCoord(box.x + box.w, box.y + box.h) != TileType::Empty)
            m_shouldDelete = true;


    } else if (m_velocity.x < 0) {

        if (m_level->getTileTypeAtCoord(box.x, box.y) != TileType::Empty || m_level->getTileTypeAtCoord(box.x, box.y + box.h) != TileType::Empty)
            m_shouldDelete = false;

    }

}
