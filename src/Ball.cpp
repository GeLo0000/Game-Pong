#include "Ball.hpp"

// Initialize ball with center position and radius
Ball::Ball(float x, float y, float radius, float windowWidth, float windowHeight)
        : m_velocity(200.0f, 150.0f), m_windowWidth(windowWidth),
            m_windowHeight(windowHeight) {
        m_shape.setRadius(radius);
        m_shape.setPosition({x - radius, y - radius}); // Center the ball
        m_shape.setFillColor(sf::Color::Yellow);
}

// Update ball position based on velocity
void Ball::update(float deltaTime) {
    sf::Vector2f pos = m_shape.getPosition();
    pos.x += m_velocity.x * deltaTime;
    pos.y += m_velocity.y * deltaTime;

    const float diameter = m_shape.getRadius() * 2.0f;

    // Bounce on top/bottom walls
    if (pos.y < 0.0f) {
        pos.y = 0.0f;
        m_velocity.y = -m_velocity.y;
    } else if (pos.y + diameter > m_windowHeight) {
        pos.y = m_windowHeight - diameter;
        m_velocity.y = -m_velocity.y;
    }

    // Reset if out of left/right bounds
    if (pos.x + diameter < 0.0f || pos.x > m_windowWidth) {
        reset();
        return;
    }

    m_shape.setPosition(pos);
}

// Render ball to target
void Ball::draw(sf::RenderTarget &target) { target.draw(m_shape); }

// Get bounding box for collision detection
sf::FloatRect Ball::getBounds() const { return m_shape.getGlobalBounds(); }

// Reset ball to center with initial velocity
void Ball::reset() {
    const float radius = m_shape.getRadius();
    m_shape.setPosition({(m_windowWidth * 0.5f) - radius,
                         (m_windowHeight * 0.5f) - radius});
    m_velocity = {200.0f, 150.0f}; // Initial velocity
}

// Set ball velocity
void Ball::setVelocity(float vx, float vy) { m_velocity = {vx, vy}; }
