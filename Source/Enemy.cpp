#include "Enemy.hpp"
#include "ResourceManager.hpp"
#include <iostream>

Enemy::Enemy(sf::Vector2i position, Level* level):
	GameObject(position, AABB(0, 0, 42, 64), level),
	m_sprite(*ResourceManager::getTexture("Assets/IceWitch.png")),
	m_velocity(4, 0),
	m_onGround(false),
	m_health(100) {

	//m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	
}

void Enemy::damage(int amount) {

	m_health -= amount;

}

void Enemy::draw(sf::RenderWindow& window) {

	m_sprite.setPosition(sf::Vector2f((float)m_position.x, (float)m_position.y));
	window.draw(m_sprite);

}

void Enemy::update() {

	m_physics.update(*this, m_level);

	if (m_health < 0)
		m_shouldDelete = true;

}

void Enemy::collided(GameObject* other) {

	if (Player* p = dynamic_cast<Player*>(other)) {
		p->setDelete();
	}

}
