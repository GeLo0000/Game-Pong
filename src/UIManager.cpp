#include "UIManager.hpp"
#include "ResourceManager.hpp"
#include "ScoreManager.hpp"

#include <cmath>
#include <string>

UIManager::UIManager(float windowWidth, float windowHeight)
    : m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_font(nullptr),
      m_scoreLabel(nullptr), m_speedLabel(nullptr) {
    ResourceManager::instance().loadFont("main_font", "assets/fonts/Roboto-Regular.ttf");
    m_font = ResourceManager::instance().getFont("main_font");

    createGameUI();
    createMenuCanvas();
    createPauseCanvas();
}

void UIManager::createGameUI() {
    if (!m_font) {
        return;
    }

    m_gameCanvas = std::make_unique<UICanvas>(sf::Vector2f{0.0f, 0.0f},
                                              sf::Vector2f{m_windowWidth, m_windowHeight});
    m_gameCanvas->setBackgroundColor(sf::Color::Transparent);

    auto scoreLabel = std::make_unique<UILabel>(sf::Vector2f{m_windowWidth / 2.0f - 50.0f, 20.0f},
                                                "0 : 0", *m_font);
    scoreLabel->setTextSize(30);
    scoreLabel->setTextColor(sf::Color::White);
    m_scoreLabel = scoreLabel.get();
    m_gameCanvas->addElement(std::move(scoreLabel));

    auto speedLabel = std::make_unique<UILabel>(
        sf::Vector2f{m_windowWidth / 2.0f - 60.0f, m_windowHeight - 40.0f}, "Ball Speed: 0",
        *m_font);
    speedLabel->setTextSize(20);
    speedLabel->setTextColor(sf::Color(150, 150, 150));
    m_speedLabel = speedLabel.get();
    m_gameCanvas->addElement(std::move(speedLabel));
}

void UIManager::createMenuCanvas() {
    if (!m_font) {
        return;
    }

    m_menuCanvas = std::make_unique<UICanvas>(sf::Vector2f{0.0f, 0.0f},
                                              sf::Vector2f{m_windowWidth, m_windowHeight});
    m_menuCanvas->setBackgroundColor(sf::Color::Transparent);

    auto titleLabel = std::make_unique<UILabel>(sf::Vector2f{m_windowWidth / 2.0f - 100.0f, 80.0f},
                                                "Pong", *m_font);
    titleLabel->setTextSize(80);
    titleLabel->setTextColor(sf::Color::White);
    m_menuCanvas->addElement(std::move(titleLabel));

    auto exitHintLabel =
        std::make_unique<UILabel>(sf::Vector2f{20.0f, 20.0f},
                                  " Esc - Exit\n Space - Pause\n R - Restart\n M - Menu", *m_font);
    exitHintLabel->setTextSize(18);
    exitHintLabel->setTextColor(sf::Color(200, 200, 200));
    m_menuCanvas->addElement(std::move(exitHintLabel));

    const float buttonWidth = 200.0f;
    const float buttonHeight = 120.0f;
    const float spacing = 100.0f;
    const float startY = m_windowHeight / 2.0f - 20.0f;
    const float centerX = m_windowWidth / 2.0f;

    auto pvpButton = std::make_unique<UIButton>(
        sf::Vector2f{centerX - buttonWidth - spacing / 2.0f, startY},
        sf::Vector2f{buttonWidth, buttonHeight}, "Player vs Player\n    (Press '1')", *m_font);
    pvpButton->setTextSize(24);
    pvpButton->setBackgroundColor(sf::Color::Transparent);
    pvpButton->setOutlineColor(sf::Color::White);
    pvpButton->setOutlineThickness(3.0f);
    m_menuCanvas->addElement(std::move(pvpButton));

    auto pvaiButton = std::make_unique<UIButton>(sf::Vector2f{centerX + spacing / 2.0f, startY},
                                                 sf::Vector2f{buttonWidth, buttonHeight},
                                                 "Player vs Bot\n  (Press '2')", *m_font);
    pvaiButton->setTextSize(24);
    pvaiButton->setBackgroundColor(sf::Color::Transparent);
    pvaiButton->setOutlineColor(sf::Color::White);
    pvaiButton->setOutlineThickness(3.0f);
    m_menuCanvas->addElement(std::move(pvaiButton));
}

void UIManager::createPauseCanvas() {
    if (!m_font) {
        return;
    }

    const float overlayWidth = 600.0f;
    const float overlayHeight = 200.0f;
    const float overlayX = m_windowWidth / 2.0f - overlayWidth / 2.0f;
    const float overlayY = m_windowHeight / 2.0f - overlayHeight / 2.0f;

    m_pauseCanvas = std::make_unique<UICanvas>(sf::Vector2f{overlayX, overlayY},
                                               sf::Vector2f{overlayWidth, overlayHeight});
    m_pauseCanvas->setBackgroundColor(sf::Color(80, 80, 80));
    m_pauseCanvas->setOutlineColor(sf::Color::Black);
    m_pauseCanvas->setOutlineThickness(3.0f);

    auto pauseTitle = std::make_unique<UILabel>(
        sf::Vector2f{m_windowWidth / 2.0f - 60.0f, overlayY + 20.0f}, "Paused", *m_font);
    pauseTitle->setTextSize(36);
    pauseTitle->setTextColor(sf::Color::White);
    m_pauseCanvas->addElement(std::move(pauseTitle));

    const float btnWidth = 135.0f;
    const float btnHeight = 50.0f;
    const float btnSpacing = 12.0f;
    const float btnStartX = overlayX + 12.0f;
    const float btnY = overlayY + overlayHeight - btnHeight - 12.0f;

    std::vector<std::string> buttonLabels = {"Continue (Space)", "Restart (R)", "Menu (M)",
                                             "Exit (Esc)"};

    for (size_t i = 0; i < buttonLabels.size(); ++i) {
        auto btn =
            std::make_unique<UIButton>(sf::Vector2f{btnStartX + i * (btnWidth + btnSpacing), btnY},
                                       sf::Vector2f{btnWidth, btnHeight}, buttonLabels[i], *m_font);
        btn->setTextSize(15);
        btn->setBackgroundColor(sf::Color(50, 50, 50));
        btn->setOutlineColor(sf::Color::Black);
        btn->setOutlineThickness(2.0f);
        m_pauseCanvas->addElement(std::move(btn));
    }
}

void UIManager::renderMenu(sf::RenderWindow &window) {
    if (m_menuCanvas) {
        m_menuCanvas->draw(window);
    }
}

void UIManager::renderGameUI(sf::RenderWindow &window, sf::Vector2f ballVelocity) {
    const int leftScore = ScoreManager::instance().getLeftScore();
    const int rightScore = ScoreManager::instance().getRightScore();
    if (m_scoreLabel) {
        m_scoreLabel->setText(std::to_string(leftScore) + " : " + std::to_string(rightScore));
    }

    if (m_speedLabel) {
        float speed = std::sqrt(ballVelocity.x * ballVelocity.x + ballVelocity.y * ballVelocity.y);
        m_speedLabel->setText("Ball Speed: " + std::to_string(static_cast<int>(speed)));
    }

    if (m_gameCanvas) {
        m_gameCanvas->draw(window);
    }
}

void UIManager::renderPause(sf::RenderWindow &window) {
    if (m_pauseCanvas) {
        m_pauseCanvas->draw(window);
    }
}
