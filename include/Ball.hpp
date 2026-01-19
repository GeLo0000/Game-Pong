#pragma once

#include "IGameObject.hpp"
#include <SFML/Graphics.hpp>

// Game ball that bounces between paddles
class Ball : public IGameObject {
  public:
    Ball(float x, float y, float radius);

    void update(float deltaTime) override;
    void draw(sf::RenderTarget &target) override;
    sf::FloatRect getBounds() const override;

    void reset();
    void setVelocity(float vx, float vy);

  private:
    sf::CircleShape m_shape;
    sf::Vector2f m_velocity;
};
