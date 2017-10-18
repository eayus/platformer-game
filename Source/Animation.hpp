#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
public:
    Animation(sf::Texture* texture, std::vector<sf::IntRect> frames, int frameDelay);
    void draw(sf::RenderWindow& window, const sf::Vector2i& position);
    void update(); // called every frame
    void setLoop(bool loop);

private:
    sf::Sprite m_sprite;
    std::vector<sf::IntRect> m_frames;
    int m_frameDelay;
    int m_currentFrameDelay;
    int m_currentFrame;
    bool m_isRunning;
    bool m_loop;

};
