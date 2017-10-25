#pragma once

#include "GameObject.hpp"
#include "Animation.hpp"

class FireBall : public GameObject
{
public:
    FireBall(const sf::Vector2i& position, const sf::Vector2i& velocity, Level* level);
    void draw(sf::RenderWindow& window) override;
    void update() override;
	void collided(GameObject* other) override;

private:
    sf::Vector2i m_velocity;
    Animation m_anim;

};
