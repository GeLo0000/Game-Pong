#pragma once

#include <SFML/Graphics.hpp>

class IUIElement {
  public:
    virtual ~IUIElement() = default;

    virtual void draw(sf::RenderWindow &window) const = 0;

    virtual sf::Vector2f getPosition() const = 0;
    virtual void setPosition(const sf::Vector2f &position) = 0;

    virtual bool contains(const sf::Vector2f &point) const = 0;
};
