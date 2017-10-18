#pragma once

#include "GameObject.hpp"
#include "Animation.hpp"

class Player : public GameObject
{
public:
    Player(const sf::Vector2i& position, Level* level);
    void draw(sf::RenderWindow& window) override;
    void update() override;
    void stepX();
    void stepY();
    void stepSlope();
    
private:
    Animation m_rightAnim;
    Animation m_leftAnim;
    Animation* m_currentAnim;
    sf::Vector2i m_velocity;
    bool m_onGround;

};
