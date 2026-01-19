#pragma once

#include "IGameObject.hpp"
#include <SFML/Graphics.hpp>

// Player paddle
class Paddle : public IGameObject {
  public:
    Paddle(float x, float y, float width, float height, float windowHeight);

    void update(float deltaTime) override;
    void draw(sf::RenderTarget &target) override;
    sf::FloatRect getBounds() const override;

    void moveUp();
    void moveDown();
    void setPosition(sf::Vector2f position);

  private:
    sf::RectangleShape m_shape;
    float m_moveSpeed;
    float m_velocityY;    // Current vertical velocity
    float m_windowHeight; // Screen height for clamping
};
