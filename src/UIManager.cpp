#include "UIManager.hpp"
#include <cmath>
#include <string>

UIManager::UIManager(float windowWidth, float windowHeight, ResourceManager &resourceMgr)
    : m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_resourceMgr(resourceMgr),
      m_font(nullptr), m_scoreLabel(nullptr), m_speedLabel(nullptr) {
    m_resourceMgr.loadFont(kFontMainName, kFontMainPath);
    m_font = m_resourceMgr.getFont(kFontMainName);

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

    auto scoreLabel = std::make_unique<UILabel>(
        sf::Vector2f{m_windowWidth / 2.0f - kScoreLabelOffsetX, kScoreLabelY},
        "0" + std::string(kScoreSeparator) + "0", *m_font);
    scoreLabel->setTextSize(kScoreLabelTextSize);
    scoreLabel->setTextColor(sf::Color::White);
    m_scoreLabel = scoreLabel.get();
    m_gameCanvas->addElement(std::move(scoreLabel));

    auto speedLabel =
        std::make_unique<UILabel>(sf::Vector2f{m_windowWidth / 2.0f - kSpeedLabelOffsetX,
                                               m_windowHeight - kSpeedLabelOffsetY},
                                  std::string(kBallSpeedPrefix) + "0", *m_font);
    speedLabel->setTextSize(kSpeedLabelTextSize);
    speedLabel->setTextColor(sf::Color(kGreyColor, kGreyColor, kGreyColor));
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

    auto titleLabel = std::make_unique<UILabel>(
        sf::Vector2f{m_windowWidth / 2.0f - kTitleLabelOffsetX, kTitleLabelY}, kMenuTitleText,
        *m_font);
    titleLabel->setTextSize(kTitleLabelTextSize);
    titleLabel->setTextColor(sf::Color::White);
    m_menuCanvas->addElement(std::move(titleLabel));

    auto exitHintLabel =
        std::make_unique<UILabel>(sf::Vector2f{kHintLabelX, kHintLabelY}, kMenuHintText, *m_font);
    exitHintLabel->setTextSize(kHintLabelTextSize);
    exitHintLabel->setTextColor(sf::Color(200, 200, 200));
    m_menuCanvas->addElement(std::move(exitHintLabel));

    const float startY = m_windowHeight / 2.0f - kButtonMenuYOffset;
    const float centerX = m_windowWidth / 2.0f;

    auto pvpButton = std::make_unique<UIButton>(
        sf::Vector2f{centerX - kButtonWidth - kButtonSpacing / 2.0f, startY},
        sf::Vector2f{kButtonWidth, kButtonHeight}, kMenuButtonPvPText, *m_font);
    pvpButton->setTextSize(kButtonTextSize);
    pvpButton->setBackgroundColor(sf::Color::Transparent);
    pvpButton->setOutlineColor(sf::Color::White);
    pvpButton->setOutlineThickness(kButtonOutlineThickness);
    m_menuCanvas->addElement(std::move(pvpButton));

    auto pvaiButton = std::make_unique<UIButton>(
        sf::Vector2f{centerX + kButtonSpacing / 2.0f, startY},
        sf::Vector2f{kButtonWidth, kButtonHeight}, kMenuButtonPvAIText, *m_font);
    pvaiButton->setTextSize(kButtonTextSize);
    pvaiButton->setBackgroundColor(sf::Color::Transparent);
    pvaiButton->setOutlineColor(sf::Color::White);
    pvaiButton->setOutlineThickness(kButtonOutlineThickness);
    m_menuCanvas->addElement(std::move(pvaiButton));
}

void UIManager::createPauseCanvas() {
    if (!m_font) {
        return;
    }

    const float overlayX = m_windowWidth / 2.0f - kPauseOverlayWidth / 2.0f;
    const float overlayY = m_windowHeight / 2.0f - kPauseOverlayHeight / 2.0f;

    m_pauseCanvas = std::make_unique<UICanvas>(
        sf::Vector2f{overlayX, overlayY}, sf::Vector2f{kPauseOverlayWidth, kPauseOverlayHeight});
    m_pauseCanvas->setBackgroundColor(
        sf::Color(kPauseCanvasBgGrey, kPauseCanvasBgGrey, kPauseCanvasBgGrey));
    m_pauseCanvas->setOutlineColor(sf::Color::Black);
    m_pauseCanvas->setOutlineThickness(kButtonOutlineThickness);

    auto pauseTitle = std::make_unique<UILabel>(
        sf::Vector2f{m_windowWidth / 2.0f - kPauseTitleOffsetX, overlayY + kPauseTitleYOffset},
        kPauseTitleText, *m_font);
    pauseTitle->setTextSize(kPauseTitleTextSize);
    pauseTitle->setTextColor(sf::Color::White);
    m_pauseCanvas->addElement(std::move(pauseTitle));

    const float btnStartX = overlayX + kPausePadding;
    const float btnY = overlayY + kPauseOverlayHeight - kPauseButtonHeight - kPausePadding;

    std::vector<std::string> buttonLabels = {kPauseButtonContinueText, kPauseButtonRestartText,
                                             kPauseButtonMenuText, kPauseButtonExitText};

    for (size_t i = 0; i < buttonLabels.size(); ++i) {
        auto btn = std::make_unique<UIButton>(
            sf::Vector2f{btnStartX + i * (kPauseButtonWidth + kPauseButtonSpacing), btnY},
            sf::Vector2f{kPauseButtonWidth, kPauseButtonHeight}, buttonLabels[i], *m_font);
        btn->setTextSize(kPauseButtonTextSize);
        btn->setBackgroundColor(
            sf::Color(kPauseButtonBgGrey, kPauseButtonBgGrey, kPauseButtonBgGrey));
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

void UIManager::renderGameUI(sf::RenderWindow &window, const Ball &ball,
                             ScoreManager &scoreManager) {
    const int leftScore = scoreManager.getLeftScore();
    const int rightScore = scoreManager.getRightScore();
    if (m_scoreLabel) {
        m_scoreLabel->setText(std::to_string(leftScore) + kScoreSeparator +
                              std::to_string(rightScore));
    }

    if (m_speedLabel) {
        sf::Vector2f ballVelocity = ball.getVelocity();
        auto speed = static_cast<int>(
            std::sqrt(ballVelocity.x * ballVelocity.x + ballVelocity.y * ballVelocity.y));
        m_speedLabel->setText(kBallSpeedPrefix + std::to_string(speed));
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
