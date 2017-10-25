#pragma once

#include "GameObject.hpp"
#include "Animation.hpp"

class Player : public GameObject
{
public:
    Player(sf::Vector2i position, Level* level);
    void draw(sf::RenderWindow& window) override;
    void update() override;
    void stepX();
    void stepY();
    void stepSlope();
	void collided(GameObject* other) override;
    
private:
    Animation m_rightAnim;
    Animation m_leftAnim;
    Animation* m_currentAnim;
    sf::Vector2i m_velocity;
    bool m_onGround;

	unsigned int m_shootDelay;

};
