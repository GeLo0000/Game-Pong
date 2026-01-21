#pragma once

#include "IUIElement.hpp"
#include <SFML/Graphics.hpp>
#include <string>

// UI Label for displaying text
class UILabel : public IUIElement {
  public:
    UILabel(const sf::Vector2f &position, const std::string &text, const sf::Font &font);

    // IUIElement interface implementation
    void draw(sf::RenderWindow &window) const override;
    sf::Vector2f getPosition() const override;
    void setPosition(const sf::Vector2f &position) override;
    bool contains(const sf::Vector2f &point) const override;

    // Label-specific methods
    void setText(const std::string &text);
    std::string getText() const;
    void setTextSize(unsigned int size);
    void setTextColor(const sf::Color &color);
    sf::FloatRect getBounds() const;

  private:
    sf::Text m_text;
};
