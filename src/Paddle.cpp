#include "Paddle.hpp"

// Initialize paddle with position and size
Paddle::Paddle(float x, float y, float width, float height, float windowHeight, bool isAI)
    : m_moveSpeed(400.0f), m_velocityY(0.0f), m_windowHeight(windowHeight), m_isAI(isAI) {
    m_shape.setSize({width, height});
    m_shape.setPosition({x, y - height / 2.0f});
    m_shape.setFillColor(sf::Color::White);
}

// Update paddle position with bounds checking
void Paddle::update(float deltaTime) {
    sf::Vector2f pos = m_shape.getPosition();
    pos.y += m_velocityY * deltaTime;

    // Clamp paddle within screen bounds
    if (pos.y < 0.0f) {
        pos.y = 0.0f;
    } else if (pos.y + m_shape.getSize().y > m_windowHeight) {
        pos.y = m_windowHeight - m_shape.getSize().y;
    }

    m_shape.setPosition(pos);
    m_velocityY = 0.0f;
}

// Render paddle to target
void Paddle::draw(sf::RenderTarget &target) { target.draw(m_shape); }

// Get bounding box for collision detection
sf::FloatRect Paddle::getBounds() const { return m_shape.getGlobalBounds(); }

// Set upward movement
void Paddle::moveUp() { m_velocityY = -m_moveSpeed; }

// Set downward movement
void Paddle::moveDown() { m_velocityY = m_moveSpeed; }

// Set paddle position directly
void Paddle::setPosition(sf::Vector2f position) { m_shape.setPosition(position); }

// AI movement logic: follow ball perfectly
void Paddle::updateAI(float ballY, float deltaTime) {
    const float paddleCenterY = m_shape.getPosition().y + m_shape.getSize().y / 2.0f;
    const float targetY = ballY;

    // Move toward target precisely
    if (targetY < paddleCenterY - 10.f) {
        moveUp();
    } else if (targetY > paddleCenterY + 10.f) {
        moveDown();
    }

    update(deltaTime);
}

bool Paddle::isAI() const { return m_isAI; }
