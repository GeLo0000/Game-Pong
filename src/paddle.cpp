#include "paddle.h"

Paddle::Paddle(float x, float y, float width, float height)
    : m_speed(0.0f)
{
    m_shape.setSize(sf::Vector2f(width, height));
    m_shape.setPosition(x, y);
    m_shape.setFillColor(sf::Color::White);
}

void Paddle::moveUp(float speed, float topBound)
{
    sf::Vector2f pos = m_shape.getPosition();
    pos.y -= speed;
    
    // Keep paddle within top boundary
    if (pos.y < topBound)
    {
        pos.y = topBound;
    }
    
    m_shape.setPosition(pos);
}

void Paddle::moveDown(float speed, float bottomBound)
{
    sf::Vector2f pos = m_shape.getPosition();
    pos.y += speed;
    
    // Keep paddle within bottom boundary (considering paddle height)
    float paddleBottom = pos.y + m_shape.getSize().y;
    if (paddleBottom > bottomBound)
    {
        pos.y = bottomBound - m_shape.getSize().y;
    }
    
    m_shape.setPosition(pos);
}

void Paddle::update()
{
    // Placeholder for future functionality (AI, smoothing, etc)
}

void Paddle::draw(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}

sf::FloatRect Paddle::getBounds() const
{
    return m_shape.getGlobalBounds();
}

sf::Vector2f Paddle::getPosition() const
{
    return m_shape.getPosition();
}

void Paddle::setPosition(float x, float y)
{
    m_shape.setPosition(x, y);
}
