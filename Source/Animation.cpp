#include "Animation.hpp"

Animation::Animation(sf::Texture* texture, const std::vector<sf::IntRect>& frames, int frameDelay):
    m_sprite(*texture),
    m_frames(std::move(frames)),
    m_frameDelay(frameDelay),
    m_currentFrameDelay(frameDelay - 1),
    m_currentFrame(0),
    m_isRunning(true),
    m_loop(true) {

}

void Animation::draw(sf::RenderWindow& window, sf::Vector2i position) {

    m_sprite.setTextureRect(m_frames.at(m_currentFrame));
    m_sprite.setPosition(float(position.x), float(position.y));
    window.draw(m_sprite);

}

void Animation::update() {

    if (!m_isRunning) return;

    m_currentFrameDelay++;
    if (m_currentFrameDelay == m_frameDelay) {

        m_currentFrame++;
        if (m_currentFrame >= m_frames.size() && m_loop)
            m_currentFrame = 0;

        m_currentFrameDelay = 0;

    }
}

void Animation::setLoop(bool loop) {

    m_loop = loop;

}
