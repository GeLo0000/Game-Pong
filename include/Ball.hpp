#pragma once

#include "IGameObject.hpp"
#include <SFML/Graphics.hpp>

class Ball : public IGameObject {
  public:
    Ball(float x, float y, float radius, float windowWidth, float windowHeight);

    void update(float deltaTime) override;
    void draw(sf::RenderTarget &target) override;
    sf::FloatRect getBounds() const override;

    void reset();
    void setVelocity(float vx, float vy);
    sf::Vector2f getVelocity() const;
    void setPosition(sf::Vector2f position) override;
    void increaseSpeed();

  private:
    static constexpr float kInitialVelocityX = 200.0f;
    static constexpr float kInitialVelocityY = 150.0f;
    static constexpr float kSpeedMultiplier = 1.05f;
    static constexpr float kMaxSpeed = 2000.0f;
    static constexpr float kBaseSpeed = 300.0f;
    static constexpr float kAngleRange = 45.0f;
    static constexpr float kPi = 3.14159f;

    sf::CircleShape m_shape;
    float m_windowWidth = 800.0f;
    float m_windowHeight = 600.0f;
};
