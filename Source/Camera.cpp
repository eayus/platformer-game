#include "Camera.hpp"
#include "Player.hpp"
#include "Constants.hpp"

Camera::Camera(int levelWidth, int levelHeight, Player* player):
	m_levelWidth(levelWidth),
	m_levelHeight(levelHeight),
	m_xAllowance(50.0f),
	m_player(player) {

	m_view.setSize(sf::Vector2f(config::window_width, config::window_height));

	m_view.setCenter(sf::Vector2f((float)m_player->getBoundingBox().getCenter().x, m_levelHeight - ((float)config::window_height / 2.0f)));

}

sf::View* Camera::getView() {

	return &m_view;

}

void Camera::update() {

	const float halfWidth = (float)config::window_width / 2.0f;

	float playerX = m_player->getBoundingBox().getCenter().x;
	float camX = m_view.getCenter().x;

	if (playerX > camX + m_xAllowance)
		camX = playerX - m_xAllowance;
	else if (playerX < camX - m_xAllowance)
		camX = playerX + m_xAllowance;


	sf::Vector2f camPos(camX, m_levelHeight - ((float)config::window_height / 2.0f));

	if (camPos.x < halfWidth) {
		camPos.x = halfWidth;	
	}

	if (camPos.x + halfWidth > (float)m_levelWidth)
		camPos.x = (float)m_levelWidth - halfWidth;

	m_view.setCenter(camPos);

}
