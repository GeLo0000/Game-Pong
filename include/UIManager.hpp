#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <optional>
#include <vector>

// Manages all UI rendering and state
class UIManager {
  public:
    UIManager(float windowWidth, float windowHeight);

    void loadFont(const sf::Font *font);
    void renderMenu(sf::RenderWindow &window);
    void renderGameUI(sf::RenderWindow &window, sf::Vector2f ballVelocity);
    void renderPause(sf::RenderWindow &window);

  private:
    void createMenuButtons();
    void createPauseMenu();
    void centerTextInButton(sf::Text &text, const sf::RectangleShape &button);

    float m_windowWidth;
    float m_windowHeight;

    // Game UI
    std::optional<sf::Text> m_scoreText;
    std::optional<sf::Text> m_speedText;

    // Main menu
    std::optional<sf::Text> m_titleText;
    std::optional<sf::Text> m_exitHintText;
    std::vector<sf::RectangleShape> m_menuButtons;
    std::vector<sf::Text> m_menuButtonTexts;

    // Pause menu
    std::optional<sf::RectangleShape> m_pauseOverlay;
    std::optional<sf::Text> m_pauseTitle;
    std::vector<sf::RectangleShape> m_pauseButtons;
    std::vector<sf::Text> m_pauseButtonTexts;
};
