#pragma once

#include <SFML/Graphics.hpp>

class Player;

class Camera
{
public:
    Camera(int levelWidth, int levelHeight, Player* player);
    sf::View* getView();
    void update();

private:
    sf::View m_view;
    int m_levelWidth;
    int m_levelHeight;
    const float m_xAllowance;
    int m_zoom;
    Player* m_player;

};
