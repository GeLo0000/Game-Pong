#include "UIManager.hpp"

#include <string>

UIManager::UIManager(float windowWidth, float windowHeight)
    : m_windowWidth(windowWidth), m_windowHeight(windowHeight) {}

void UIManager::loadFont(const sf::Font *font) {
    if (!font) {
        return;
    }

    // Score text
    m_scoreText = sf::Text(*font);
    m_scoreText->setCharacterSize(30);
    m_scoreText->setFillColor(sf::Color::White);
    m_scoreText->setPosition({m_windowWidth / 2.0f - 50.0f, 20.0f});

    // Pause text
    m_pausedText = sf::Text(*font);
    m_pausedText->setString("PAUSED");
    m_pausedText->setCharacterSize(40);
    m_pausedText->setFillColor(sf::Color::White);
    m_pausedText->setPosition(
        {m_windowWidth / 2.0f - 80.0f, m_windowHeight / 2.0f - 20.0f});

    // Menu text
    m_menuText = sf::Text(*font);
    m_menuText->setString(
        "PONG\n\n1 - PvP (W/S vs Up/Down)\n2 - PvAI (W/S vs AI)\nESC - Quit");
    m_menuText->setCharacterSize(26);
    m_menuText->setFillColor(sf::Color::White);
    m_menuText->setPosition({80.0f, 120.0f});
}

void UIManager::renderMenu(sf::RenderWindow &window) {
    if (m_menuText) {
        window.draw(*m_menuText);
    }
}

void UIManager::renderGameUI(sf::RenderWindow &window, int leftScore,
                             int rightScore) {
    if (m_scoreText) {
        m_scoreText->setString(std::to_string(leftScore) + " : " +
                               std::to_string(rightScore));
        window.draw(*m_scoreText);
    }
}

void UIManager::renderPause(sf::RenderWindow &window) {
    if (m_pausedText) {
        window.draw(*m_pausedText);
    }
}
