#include "UIManager.hpp"
#include "ScoreManager.hpp"

#include <cmath>
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

    // Speed text
    m_speedText = sf::Text(*font);
    m_speedText->setCharacterSize(20);
    m_speedText->setFillColor(sf::Color(150, 150, 150));
    m_speedText->setPosition({m_windowWidth / 2.0f - 60.0f, m_windowHeight - 40.0f});

    // Main menu title
    m_titleText = sf::Text(*font);
    m_titleText->setString("Pong");
    m_titleText->setCharacterSize(80);
    m_titleText->setFillColor(sf::Color::White);
    m_titleText->setPosition({m_windowWidth / 2.0f - 100.0f, 80.0f});

    // Exit hint
    m_exitHintText = sf::Text(*font);
    m_exitHintText->setString("Press Esc to exit");
    m_exitHintText->setCharacterSize(18);
    m_exitHintText->setFillColor(sf::Color(200, 200, 200));
    m_exitHintText->setPosition({20.0f, 20.0f});

    createMenuButtons();
    createPauseMenu();
}

void UIManager::createMenuButtons() {
    const float buttonWidth = 200.0f;
    const float buttonHeight = 120.0f;
    const float spacing = 100.0f;
    const float startY = m_windowHeight / 2.0f - 20.0f;
    const float centerX = m_windowWidth / 2.0f;

    // PvP button
    sf::RectangleShape pvpButton({buttonWidth, buttonHeight});
    pvpButton.setPosition({centerX - buttonWidth - spacing / 2.0f, startY});
    pvpButton.setFillColor(sf::Color::Transparent);
    pvpButton.setOutlineColor(sf::Color::White);
    pvpButton.setOutlineThickness(3.0f);
    m_menuButtons.push_back(pvpButton);

    sf::Text pvpText(m_scoreText->getFont());
    pvpText.setString("Player vs Player");
    pvpText.setCharacterSize(24);
    pvpText.setFillColor(sf::Color::White);
    centerTextInButton(pvpText, pvpButton);
    m_menuButtonTexts.push_back(pvpText);

    // PvAI button
    sf::RectangleShape pvaiButton({buttonWidth, buttonHeight});
    pvaiButton.setPosition({centerX + spacing / 2.0f, startY});
    pvaiButton.setFillColor(sf::Color::Transparent);
    pvaiButton.setOutlineColor(sf::Color::White);
    pvaiButton.setOutlineThickness(3.0f);
    m_menuButtons.push_back(pvaiButton);

    sf::Text pvaiText(m_scoreText->getFont());
    pvaiText.setString("Player vs Bot");
    pvaiText.setCharacterSize(24);
    pvaiText.setFillColor(sf::Color::White);
    centerTextInButton(pvaiText, pvaiButton);
    m_menuButtonTexts.push_back(pvaiText);
}

void UIManager::createPauseMenu() {
    // Gray overlay
    const float overlayWidth = 600.0f;
    const float overlayHeight = 200.0f;
    const float overlayX = m_windowWidth / 2.0f - overlayWidth / 2.0f;
    const float overlayY = m_windowHeight / 2.0f - overlayHeight / 2.0f;

    m_pauseOverlay = sf::RectangleShape({overlayWidth, overlayHeight});
    m_pauseOverlay->setPosition({overlayX, overlayY});
    m_pauseOverlay->setFillColor(sf::Color(80, 80, 80));
    m_pauseOverlay->setOutlineColor(sf::Color::Black);
    m_pauseOverlay->setOutlineThickness(3.0f);

    // Pause title
    m_pauseTitle = sf::Text(m_scoreText->getFont());
    m_pauseTitle->setString("Paused");
    m_pauseTitle->setCharacterSize(36);
    m_pauseTitle->setFillColor(sf::Color::White);
    m_pauseTitle->setPosition({m_windowWidth / 2.0f - 60.0f, overlayY + 20.0f});

    // Pause buttons
    const float btnWidth = 135.0f;
    const float btnHeight = 50.0f;
    const float btnSpacing = 12.0f;
    const float btnStartX = overlayX + 12.0f;
    const float btnY = overlayY + overlayHeight - btnHeight - 12.0f;

    std::vector<std::string> buttonLabels = {"Continue (Space)", "Restart (R)", "Menu (M)",
                                             "Exit (Esc)"};

    for (size_t i = 0; i < buttonLabels.size(); ++i) {
        sf::RectangleShape btn({btnWidth, btnHeight});
        btn.setPosition({btnStartX + i * (btnWidth + btnSpacing), btnY});
        btn.setFillColor(sf::Color(50, 50, 50));
        btn.setOutlineColor(sf::Color::Black);
        btn.setOutlineThickness(2.0f);
        m_pauseButtons.push_back(btn);

        sf::Text btnText(m_scoreText->getFont());
        btnText.setString(buttonLabels[i]);
        btnText.setCharacterSize(15);
        btnText.setFillColor(sf::Color::White);
        centerTextInButton(btnText, btn);
        m_pauseButtonTexts.push_back(btnText);
    }
}

void UIManager::renderMenu(sf::RenderWindow &window) {
    // Draw title
    if (m_titleText) {
        window.draw(*m_titleText);
    }

    // Draw exit hint
    if (m_exitHintText) {
        window.draw(*m_exitHintText);
    }

    // Draw menu buttons
    for (const auto &button : m_menuButtons) {
        window.draw(button);
    }
    for (const auto &text : m_menuButtonTexts) {
        window.draw(text);
    }
}

void UIManager::renderGameUI(sf::RenderWindow &window, sf::Vector2f ballVelocity) {
    const int leftScore = ScoreManager::instance().getLeftScore();
    const int rightScore = ScoreManager::instance().getRightScore();
    if (m_scoreText) {
        m_scoreText->setString(std::to_string(leftScore) + " : " + std::to_string(rightScore));
        window.draw(*m_scoreText);
    }

    // Calculate and display ball speed
    if (m_speedText) {
        float speed = std::sqrt(ballVelocity.x * ballVelocity.x + ballVelocity.y * ballVelocity.y);
        m_speedText->setString("Ball Speed: " + std::to_string(static_cast<int>(speed)));
        window.draw(*m_speedText);
    }
}

void UIManager::renderPause(sf::RenderWindow &window) {
    // Draw gray overlay
    if (m_pauseOverlay) {
        window.draw(*m_pauseOverlay);
    }

    // Draw pause title
    if (m_pauseTitle) {
        window.draw(*m_pauseTitle);
    }

    // Draw pause buttons
    for (const auto &button : m_pauseButtons) {
        window.draw(button);
    }
    for (const auto &text : m_pauseButtonTexts) {
        window.draw(text);
    }
}

void UIManager::centerTextInButton(sf::Text &text, const sf::RectangleShape &button) {
    auto bounds = text.getLocalBounds();
    text.setPosition({button.getPosition().x + (button.getSize().x - bounds.size.x) / 2.0f,
                      button.getPosition().y + (button.getSize().y - bounds.size.y) / 2.0f});
}
