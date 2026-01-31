#include "UIButton.hpp"

UIButton::UIButton(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &text,
                   const sf::Font &font)
    : m_text(font), m_normalColor(sf::Color::Transparent),
      m_hoverColor(sf::Color(kHoverBgGrey, kHoverBgGrey, kHoverBgGrey, kHoverBgAlpha)),
      m_outlineColor(sf::Color::White) {

    m_background.setPosition(position);
    m_background.setSize(size);
    m_background.setFillColor(m_normalColor);
    m_background.setOutlineColor(m_outlineColor);
    m_background.setOutlineThickness(kOutlineThickness);

    m_text.setString(text);
    m_text.setCharacterSize(kDefaultTextSize);
    m_text.setFillColor(sf::Color::White);

    centerText();
}

void UIButton::draw(sf::RenderWindow &window) const {
    window.draw(m_background);
    window.draw(m_text);
}

sf::Vector2f UIButton::getPosition() const { return m_background.getPosition(); }

void UIButton::setPosition(const sf::Vector2f &position) {
    m_background.setPosition(position);
    centerText();
}

bool UIButton::contains(const sf::Vector2f &point) const {
    return m_background.getGlobalBounds().contains(point);
}

void UIButton::setText(const std::string &text) {
    m_text.setString(text);
    centerText();
}

void UIButton::setTextSize(unsigned int size) {
    m_text.setCharacterSize(size);
    centerText();
}

void UIButton::setTextColor(const sf::Color &color) { m_text.setFillColor(color); }

void UIButton::setBackgroundColor(const sf::Color &color) {
    m_normalColor = color;
    if (!m_isHovered) {
        m_background.setFillColor(m_normalColor);
    }
}

void UIButton::setOutlineColor(const sf::Color &color) {
    m_outlineColor = color;
    m_background.setOutlineColor(m_outlineColor);
}

void UIButton::setOutlineThickness(float thickness) {
    m_background.setOutlineThickness(thickness);
    centerText();
}

void UIButton::setSize(const sf::Vector2f &size) {
    m_background.setSize(size);
    centerText();
}

void UIButton::setHovered(bool hovered) {
    m_isHovered = hovered;
    m_background.setFillColor(hovered ? m_hoverColor : m_normalColor);
}

bool UIButton::isHovered() const { return m_isHovered; }

sf::Vector2f UIButton::getSize() const { return m_background.getSize(); }

void UIButton::centerText() {
    auto bounds = m_text.getLocalBounds();
    auto bgPos = m_background.getPosition();
    auto bgSize = m_background.getSize();

    m_text.setPosition(
        {bgPos.x + (bgSize.x - bounds.size.x) / 2.0f, bgPos.y + (bgSize.y - bounds.size.y) / 2.0f});
}
