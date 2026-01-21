#pragma once

#include <SFML/Graphics.hpp>

// Base interface for all UI elements
class IUIElement {
  public:
    virtual ~IUIElement() = default;

    // Render the UI element to the window
    virtual void draw(sf::RenderWindow &window) const = 0;

    // Get the position of the UI element
    virtual sf::Vector2f getPosition() const = 0;

    // Set the position of the UI element
    virtual void setPosition(const sf::Vector2f &position) = 0;

    // Check if a point is within the UI element bounds (for mouse interaction)
    virtual bool contains(const sf::Vector2f &point) const = 0;
};
