#pragma once

#include "UIButton.hpp"
#include "UICanvas.hpp"
#include "UILabel.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

// Manages all UI rendering and state
class UIManager {
  public:
    UIManager(float windowWidth, float windowHeight);

    void renderMenu(sf::RenderWindow &window);
    void renderGameUI(sf::RenderWindow &window, sf::Vector2f ballVelocity);
    void renderPause(sf::RenderWindow &window);

  private:
    void createGameUI();
    void createMenuCanvas();
    void createPauseCanvas();

    float m_windowWidth;
    float m_windowHeight;

    const sf::Font *m_font;

    std::unique_ptr<UICanvas> m_gameCanvas;
    UILabel *m_scoreLabel;
    UILabel *m_speedLabel;

    std::unique_ptr<UICanvas> m_menuCanvas;

    std::unique_ptr<UICanvas> m_pauseCanvas;
};
