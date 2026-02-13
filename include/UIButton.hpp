#pragma once

#include "IUIElement.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class UIButton : public IUIElement {
  public:
    UIButton(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &text,
             const sf::Font &font);

    void draw(sf::RenderWindow &window) const override;
    sf::Vector2f getPosition() const override;
    void setPosition(const sf::Vector2f &position) override;
    bool contains(const sf::Vector2f &point) const override;

    void setText(const std::string &text);
    void setTextSize(unsigned int size);
    void setTextColor(const sf::Color &color);
    void setBackgroundColor(const sf::Color &color);
    void setOutlineColor(const sf::Color &color);
    void setOutlineThickness(float thickness);
    void setSize(const sf::Vector2f &size);

    void setHovered(bool hovered);
    bool isHovered() const;

    sf::Vector2f getSize() const;

  private:
    void centerText();

    static constexpr float kOutlineThickness = 3.0f;
    static constexpr unsigned int kDefaultTextSize = 24;
    static constexpr int kHoverBgGrey = 50;
    static constexpr int kHoverBgAlpha = 100;

    sf::RectangleShape m_background;
    sf::Text m_text;
    bool m_isHovered = false;

    sf::Color m_normalColor;
    sf::Color m_hoverColor;
    sf::Color m_outlineColor;
};
