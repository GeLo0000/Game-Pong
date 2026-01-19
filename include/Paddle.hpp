#pragma once

#include "IGameObject.hpp"
#include <SFML/Graphics.hpp>

// Player paddle
class Paddle : public IGameObject {
  public:
    Paddle(float x, float y, float width, float height, float windowHeight,
           bool isAI = false, bool invincible = false);

    void update(float deltaTime) override;
    void updateAI(float ballY, float deltaTime); // AI movement logic
    void draw(sf::RenderTarget &target) override;
    sf::FloatRect getBounds() const override;

    void moveUp();
    void moveDown();
    void setPosition(sf::Vector2f position);

    bool isAI() const;

  private:
    sf::RectangleShape m_shape;
    float m_moveSpeed;
    float m_velocityY;     // Current vertical velocity
    float m_windowHeight;  // Screen height for clamping
    bool m_isAI;           // AI-controlled flag
    bool m_invincible;     // Perfect AI (no mistakes)
    float m_aiErrorMargin; // AI tracking offset for difficulty
};
