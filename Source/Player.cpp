#include "Player.hpp"
#include "Level.hpp"
#include "ResourceManager.hpp"
#include "FireBall.hpp"
#include <iostream>
#include "Enemy.hpp"

Player::Player(sf::Vector2i position, Level* level):
    GameObject(position, AABB(10, 0, 44, 64), level),
    m_rightAnim(ResourceManager::getTexture("Assets/FoxGirl.png"), std::vector<sf::IntRect>{ sf::IntRect({0, 0}, {64, 64}) }, 100),
    //m_rightAnim(ResourceManager::getTexture("Assets/Player.png"), std::vector<sf::IntRect>{ sf::IntRect(0, 64, 32, 32), sf::IntRect(32, 64, 32, 32), sf::IntRect(64, 64, 32, 32), sf::IntRect(32, 64, 32, 32) }, 20),
    m_leftAnim(ResourceManager::getTexture("Assets/Player.png"), std::vector<sf::IntRect>{ sf::IntRect({0, 32}, {32, 32}), sf::IntRect({32, 32}, {32, 32}), sf::IntRect({64, 32}, {32, 32}), sf::IntRect({32, 32}, {32, 32}) }, 20),
    m_currentAnim(&m_rightAnim),
    m_velocity(0, 0),
    m_onGround(false),
    m_dashTimer(0),
    m_lastDirection(Direction::Right) {

}

void Player::draw(sf::RenderWindow& window) {

    m_currentAnim->draw(window, m_position);

}

void Player::stepX() {

    if (m_velocity.x == 0) return;

    if (m_dashTimer == 0) {

    if (m_velocity.x > 4)
        m_velocity.x = 4;
    else if (m_velocity.x < -4)
        m_velocity.x = -4;

    }


    AABB box = this->getBoundingBox();

    int lowerBound = box.y;
    int upperBound = box.y + box.h - 1;

    int distance = 0;

    for (; lowerBound <= upperBound; lowerBound += box.h - 1) {

        TileType type;

        if (m_velocity.x > 0) {

            int tileLeft = m_level->roundDownToTileSize(box.x + box.w + m_velocity.x);
            type = m_level->getTileTypeAtCoord(box.x + box.w + m_velocity.x, lowerBound);
            distance = tileLeft - (box.x + box.w);

            if (type == TileType::Solid) {
                m_velocity.x = 0;
                m_position.x += distance;
            }


        } else if (m_velocity.x < 0) {

            int tileRight = m_level->roundDownToTileSize(box.x + m_velocity.x) + 32;
            type = m_level->getTileTypeAtCoord(box.x + m_velocity.x, lowerBound);
            distance = tileRight - box.x;

            if (type == TileType::Solid) {
                m_velocity.x = 0;
                m_position.x += distance;
            }

        } 

    }

    if (m_velocity.x == 0)
	m_dashTimer = 0;


    m_position.x += m_velocity.x;
    if (m_dashTimer == 0)
	    m_velocity.x += m_velocity.x > 0 ? -2 : 2;
    //m_velocity.x = 0;
    
    if (m_dashTimer > 0)
	m_dashTimer--;

}

void Player::stepY() {

    //Gravity;
    m_velocity.y += 1;

    if (m_velocity.y > 12)
        m_velocity.y = 12;

    AABB box = this->getBoundingBox();

    int lowerBound = box.x;
    int upperBound = box.x + box.w - 1;

    int distance = 0;
    m_onGround = false;

    for (; lowerBound <= upperBound; lowerBound += box.w - 1) {

        TileType type;

        if (m_velocity.y > 0) {

            int tileTop = m_level->roundDownToTileSize(box.y + box.h + m_velocity.y);
            type = m_level->getTileTypeAtCoord(lowerBound, box.y + box.h + m_velocity.y);
            distance = tileTop - (box.y + box.h);

            if (type == TileType::Solid) {
                m_velocity.y = 0;
                m_position.y += distance;
                m_onGround = true;
            }

        } else if (m_velocity.y < 0) {
            
            int tileBottom = m_level->roundDownToTileSize(box.y + m_velocity.y) + 32;
            type = m_level->getTileTypeAtCoord(lowerBound, box.y + m_velocity.y);
            distance = tileBottom - box.y;

            if (type == TileType::Solid) {
                m_velocity.y = 0;
                m_position.y += distance;
            }

        } 

    }

    m_position.y += m_velocity.y;
  
}

void Player::stepSlope() {
    
    AABB box = this->getBoundingBox();
    
    //Left Slope
    if (m_level->getTileTypeAtCoord(box.x, box.y + box.h - 1) == TileType::LeftSlope) {

        int tileLeft = m_level->roundDownToTileSize(box.x);
        int tileTop = m_level->roundDownToTileSize(box.y + box.h - 1);

        //distnace from top right
        if ((tileLeft + 32 - box.x) + (box.y + box.h - tileTop) < 32)
            return;

        m_position.y = tileTop - box.h + (box.x - tileLeft);
        m_onGround = true;
        m_velocity.y = 0;

    }

    //Right Slope
    if (m_level->getTileTypeAtCoord(box.x + box.w - 1, box.y + box.h - 1) == TileType::RightSlope) {

        int tileLeft = m_level->roundDownToTileSize(box.x + box.w - 1);
        int tileTop = m_level->roundDownToTileSize(box.y + box.h - 1);

        if ((box.x + box.w - tileLeft) + (box.y + box.h - tileTop) < 32)
            return;

        m_position.y = tileTop - box.h + 32 - ( box.x + box.w - tileLeft);
        m_onGround = true;
        m_velocity.y = 0;

    }


}

void Player::update() {

    m_currentAnim->update();

    bool leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    bool rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);

    if (m_dashTimer == 0) {
    if (leftPressed) {
        m_velocity.x -= 4;
	m_lastDirection = Direction::Left;
    }

    if (rightPressed) {
        m_velocity.x += 4;
	m_lastDirection = Direction::Right;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {

		sf::Vector2i playerPos = this->getBoundingBox().getCenter();
		if (m_shootDelay > 100) {
			m_level->createObject(std::make_unique<FireBall>(sf::Vector2i(playerPos.x + 3, playerPos.y - 8), sf::Vector2i(5, 0), m_level));
			m_shootDelay = 0;
		}

    }
	m_shootDelay++;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && m_onGround)
        m_velocity.y -= 15;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {

        // Dash code here...	
	m_dashTimer = 30;

	m_velocity.x = (m_lastDirection == Direction::Right) ? 10 : -10;

    }
    }

    /*if (m_velocity.x < 0)
        m_currentAnim = &m_leftAnim;
    else
        m_currentAnim = &m_rightAnim;*/
    m_currentAnim = &m_rightAnim;
    
    this->stepX();
    this->stepY();
    this->stepSlope();

}

void Player::collided(GameObject* other) {

}
