#pragma once

#include "IUIElement.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

// Canvas that holds and manages multiple UI elements
class UICanvas {
  public:
    UICanvas(const sf::Vector2f &position, const sf::Vector2f &size);

    // Add UI elements to canvas
    void addElement(std::unique_ptr<IUIElement> element);

    // Clear all elements
    void clear();

    // Draw canvas background and all elements
    void draw(sf::RenderWindow &window) const;

    // Canvas background styling
    void setBackgroundColor(const sf::Color &color);
    void setOutlineColor(const sf::Color &color);
    void setOutlineThickness(float thickness);
    void setVisible(bool visible);
    bool isVisible() const;

    // Canvas position and size
    void setPosition(const sf::Vector2f &position);
    void setSize(const sf::Vector2f &size);
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;

    // Access elements
    const std::vector<std::unique_ptr<IUIElement>> &getElements() const;
    std::vector<std::unique_ptr<IUIElement>> &getElements();

  private:
    sf::RectangleShape m_background;
    std::vector<std::unique_ptr<IUIElement>> m_elements;
    bool m_visible;
};
