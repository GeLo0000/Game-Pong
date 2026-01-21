#pragma once

#include "IUIElement.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

// UI Button with text, background, and click functionality
class UIButton : public IUIElement {
  public:
    UIButton(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &text,
             const sf::Font &font);

    // IUIElement interface implementation
    void draw(sf::RenderWindow &window) const override;
    sf::Vector2f getPosition() const override;
    void setPosition(const sf::Vector2f &position) override;
    bool contains(const sf::Vector2f &point) const override;

    // Button-specific methods
    void setText(const std::string &text);
    void setTextSize(unsigned int size);
    void setTextColor(const sf::Color &color);
    void setBackgroundColor(const sf::Color &color);
    void setOutlineColor(const sf::Color &color);
    void setOutlineThickness(float thickness);
    void setSize(const sf::Vector2f &size);

    // Mouse interaction
    void setHovered(bool hovered);
    bool isHovered() const;

    // Get button dimensions
    sf::Vector2f getSize() const;

  private:
    void centerText();

    sf::RectangleShape m_background;
    sf::Text m_text;
    bool m_isHovered;

    // Colors for different states
    sf::Color m_normalColor;
    sf::Color m_hoverColor;
    sf::Color m_outlineColor;
};
