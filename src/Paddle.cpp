#include "Paddle.hpp"

Paddle::Paddle(float x, float y, float width, float height, float windowHeight)
    : m_velocityY(0.0f), m_windowHeight(windowHeight) {
    m_shape.setSize({width, height});
    m_shape.setPosition({x, y - height / 2.0f});
    m_shape.setFillColor(sf::Color::White);
}

void Paddle::update(float deltaTime) {
    sf::Vector2f pos = m_shape.getPosition();
    pos.y += m_velocityY * deltaTime;

    if (pos.y < 0.0f) {
        pos.y = 0.0f;
    } else if (pos.y + m_shape.getSize().y > m_windowHeight) {
        pos.y = m_windowHeight - m_shape.getSize().y;
    }

    m_shape.setPosition(pos);
    m_velocityY = 0.0f;
}

void Paddle::draw(sf::RenderTarget &target) { target.draw(m_shape); }

sf::FloatRect Paddle::getBounds() const { return m_shape.getGlobalBounds(); }

void Paddle::moveUp() { m_velocityY = -kMoveSpeed; }

void Paddle::moveDown() { m_velocityY = kMoveSpeed; }

void Paddle::setPosition(sf::Vector2f position) { m_shape.setPosition(position); }
