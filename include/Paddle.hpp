#pragma once

#include "IGameObject.hpp"
#include <SFML/Graphics.hpp>

class Paddle : public IGameObject {
  public:
    Paddle(float x, float y, float width, float height, float windowHeight);

    void update(float deltaTime) override;
    void draw(sf::RenderTarget &target) override;
    sf::FloatRect getBounds() const override;

    void moveUp();
    void moveDown();
    void setPosition(sf::Vector2f position);

  protected:
    static constexpr float kMoveSpeed = 400.0f;

    sf::RectangleShape m_shape;
    float m_velocityY;
    float m_windowHeight;

  private:
};
