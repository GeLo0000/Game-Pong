#include "UICanvas.hpp"

UICanvas::UICanvas(const sf::Vector2f &position, const sf::Vector2f &size) : m_visible(true) {
    m_background.setPosition(position);
    m_background.setSize(size);
    m_background.setFillColor(sf::Color::Transparent);
    m_background.setOutlineColor(sf::Color::White);
    m_background.setOutlineThickness(0.0f);
}

void UICanvas::addElement(std::unique_ptr<IUIElement> element) {
    if (element) {
        m_elements.push_back(std::move(element));
    }
}

void UICanvas::clear() { m_elements.clear(); }

void UICanvas::draw(sf::RenderWindow &window) const {
    if (!m_visible) {
        return;
    }

    window.draw(m_background);

    for (const auto &element : m_elements) {
        if (element) {
            element->draw(window);
        }
    }
}

void UICanvas::setBackgroundColor(const sf::Color &color) { m_background.setFillColor(color); }

void UICanvas::setOutlineColor(const sf::Color &color) { m_background.setOutlineColor(color); }

void UICanvas::setOutlineThickness(float thickness) { m_background.setOutlineThickness(thickness); }

void UICanvas::setVisible(bool visible) { m_visible = visible; }

bool UICanvas::isVisible() const { return m_visible; }

void UICanvas::setPosition(const sf::Vector2f &position) { m_background.setPosition(position); }

void UICanvas::setSize(const sf::Vector2f &size) { m_background.setSize(size); }

sf::Vector2f UICanvas::getPosition() const { return m_background.getPosition(); }

sf::Vector2f UICanvas::getSize() const { return m_background.getSize(); }

const std::vector<std::unique_ptr<IUIElement>> &UICanvas::getElements() const { return m_elements; }

std::vector<std::unique_ptr<IUIElement>> &UICanvas::getElements() { return m_elements; }
