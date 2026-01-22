#pragma once

#include "IGameObject.hpp"
#include <SFML/Graphics.hpp>

// Player paddle
class Paddle : public IGameObject {
  public:
    Paddle(float x, float y, float width, float height, float windowHeight, bool isAI = false);

    void update(float deltaTime) override;
    void updateAI(float ballY, float deltaTime);
    void draw(sf::RenderTarget &target) override;
    sf::FloatRect getBounds() const override;

    void moveUp();
    void moveDown();
    void setPosition(sf::Vector2f position);

  private:
    sf::RectangleShape m_shape;
    float m_moveSpeed;
    float m_velocityY;
    float m_windowHeight;
    bool m_isAI;
};
