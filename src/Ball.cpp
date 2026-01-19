#include "Ball.hpp"

// Initialize ball with center position and radius
Ball::Ball(float x, float y, float radius) : m_velocity(0.0f, 0.0f) {
    m_shape.setRadius(radius);
    m_shape.setPosition({x - radius, y - radius}); // Center the ball
    m_shape.setFillColor(sf::Color::Yellow);
}

// Update ball position based on velocity
void Ball::update(float deltaTime) {
    sf::Vector2f pos = m_shape.getPosition();
    pos.x += m_velocity.x * deltaTime;
    pos.y += m_velocity.y * deltaTime;
    m_shape.setPosition(pos);
}

// Render ball to target
void Ball::draw(sf::RenderTarget &target) { target.draw(m_shape); }

// Get bounding box for collision detection
sf::FloatRect Ball::getBounds() const { return m_shape.getGlobalBounds(); }

// Reset ball to center with initial velocity
void Ball::reset() {
    m_shape.setPosition({400.0f - m_shape.getRadius(),
                         300.0f - m_shape.getRadius()}); // Center (800x600)
    m_velocity = {200.0f, 150.0f};                       // Initial velocity
}

// Set ball velocity
void Ball::setVelocity(float vx, float vy) { m_velocity = {vx, vy}; }
