#pragma once

#include <SFML/Graphics.hpp>

class IGameObject {
  public:
    virtual ~IGameObject() = default;

    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderTarget &target) = 0;
    virtual sf::FloatRect getBounds() const = 0;
    virtual void setPosition(sf::Vector2f position) = 0;

  protected:
    sf::Vector2f m_velocity{0.0f, 0.0f};
};
