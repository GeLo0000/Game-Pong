#include "UILabel.hpp"

UILabel::UILabel(const sf::Vector2f &position, const std::string &text, const sf::Font &font)
    : m_text(font) {
    m_text.setString(text);
    m_text.setCharacterSize(kDefaultTextSize);
    m_text.setFillColor(sf::Color::White);
    m_text.setPosition(position);
}

void UILabel::draw(sf::RenderWindow &window) const { window.draw(m_text); }

sf::Vector2f UILabel::getPosition() const { return m_text.getPosition(); }

void UILabel::setPosition(const sf::Vector2f &position) { m_text.setPosition(position); }

bool UILabel::contains(const sf::Vector2f &point) const {
    return m_text.getGlobalBounds().contains(point);
}

void UILabel::setText(const std::string &text) { m_text.setString(text); }

std::string UILabel::getText() const { return m_text.getString(); }

void UILabel::setTextSize(unsigned int size) { m_text.setCharacterSize(size); }

void UILabel::setTextColor(const sf::Color &color) { m_text.setFillColor(color); }

sf::FloatRect UILabel::getBounds() const { return m_text.getGlobalBounds(); }
