#pragma once

#include <SFML/Graphics.hpp>

// Abstract base class for all game objects
class IGameObject {
  public:
    virtual ~IGameObject() = default;

    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderTarget &target) = 0;
    virtual sf::FloatRect getBounds() const = 0;
};
