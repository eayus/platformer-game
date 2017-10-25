#pragma once

#include "GameObject.hpp"
#include "PhysicsComponent.hpp"

class Enemy : public GameObject
{
	friend class PhysicsComponent;
public:
	Enemy(sf::Vector2i position, Level* level);
	void damage(int amount);
	void draw(sf::RenderWindow& window) override;
	void update() override;
	void collided(GameObject* other) override;

private:
	sf::Sprite m_sprite;
	sf::Vector2i m_velocity;
	bool m_onGround;
	int m_health;
	PhysicsComponent m_physics;

};
