#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <optional>

// Manages all UI rendering and state
class UIManager {
public:
    UIManager(float windowWidth, float windowHeight);

    void loadFont(const sf::Font *font);
    void renderMenu(sf::RenderWindow &window);
    void renderGameUI(sf::RenderWindow &window, int leftScore, int rightScore);
    void renderPause(sf::RenderWindow &window);

private:
    float m_windowWidth;
    float m_windowHeight;
    std::optional<sf::Text> m_scoreText;
    std::optional<sf::Text> m_pausedText;
    std::optional<sf::Text> m_menuText;
};
