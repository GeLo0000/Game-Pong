#include "Ball.hpp"

#include <cmath>
#include <random>

Ball::Ball(float x, float y, float radius, float windowWidth, float windowHeight)
    : m_velocity(200.0f, 150.0f), m_windowWidth(windowWidth), m_windowHeight(windowHeight),
      m_speedMultiplier(1.05f), m_maxSpeed(2000.0f) {
    m_shape.setRadius(radius);
    m_shape.setPosition({x - radius, y - radius});
    m_shape.setFillColor(sf::Color::Yellow);
}

void Ball::update(float deltaTime) {
    sf::Vector2f pos = m_shape.getPosition();
    pos.x += m_velocity.x * deltaTime;
    pos.y += m_velocity.y * deltaTime;
    m_shape.setPosition(pos);
}

void Ball::draw(sf::RenderTarget &target) { target.draw(m_shape); }

sf::FloatRect Ball::getBounds() const { return m_shape.getGlobalBounds(); }

void Ball::reset() {
    const float radius = m_shape.getRadius();
    m_shape.setPosition({(m_windowWidth * 0.5f) - radius, (m_windowHeight * 0.5f) - radius});

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> angleDist(-45.0f, 45.0f);
    std::uniform_int_distribution<int> dirDist(0, 1);

    float angle = angleDist(gen);
    float radians = angle * 3.14159f / 180.0f;
    float baseSpeed = 300.0f;
    float dirX = dirDist(gen) == 0 ? 1.0f : -1.0f;

    m_velocity = {dirX * baseSpeed * std::cos(radians), baseSpeed * std::sin(radians)};
}

void Ball::setVelocity(float vx, float vy) { m_velocity = {vx, vy}; }

sf::Vector2f Ball::getVelocity() const { return m_velocity; }

void Ball::setPosition(sf::Vector2f position) { m_shape.setPosition(position); }

void Ball::increaseSpeed() {
    float currentSpeed = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
    if (currentSpeed >= m_maxSpeed) {
        return;
    }
    m_velocity.x *= m_speedMultiplier;
    m_velocity.y *= m_speedMultiplier;

    float newSpeed = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
    if (newSpeed > m_maxSpeed) {
        float scale = m_maxSpeed / newSpeed;
        m_velocity.x *= scale;
        m_velocity.y *= scale;
    }
}
