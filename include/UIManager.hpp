#pragma once

#include "Ball.hpp"
#include "ResourceManager.hpp"
#include "ScoreManager.hpp"
#include "UIButton.hpp"
#include "UICanvas.hpp"
#include "UILabel.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class UIManager {
  public:
    UIManager(float windowWidth, float windowHeight, ResourceManager &resourceMgr);

    void renderMenu(sf::RenderWindow &window);
    void renderGameUI(sf::RenderWindow &window, const Ball &ball, ScoreManager &scoreManager);
    void renderPause(sf::RenderWindow &window);

  private:
    void createGameUI();
    void createMenuCanvas();
    void createPauseCanvas();

    static constexpr auto kFontMainName = "Roboto-Regular";
    static constexpr auto kFontMainPath = "assets/fonts/Roboto-Regular.ttf";

    static constexpr auto kScoreSeparator = " : ";
    static constexpr float kScoreLabelOffsetX = 50.0f;
    static constexpr float kScoreLabelY = 20.0f;
    static constexpr int kScoreLabelTextSize = 30;

    static constexpr auto kBallSpeedPrefix = "Ball Speed: ";
    static constexpr float kSpeedLabelOffsetX = 60.0f;
    static constexpr float kSpeedLabelOffsetY = 40.0f;
    static constexpr int kSpeedLabelTextSize = 20;

    static constexpr auto kMenuTitleText = "Pong";
    static constexpr int kTitleLabelTextSize = 80;
    static constexpr float kTitleLabelOffsetX = 100.0f;
    static constexpr float kTitleLabelY = 80.0f;

    static constexpr auto kMenuHintText = " Esc - Exit\n Space - Pause\n R - Restart\n M - Menu";
    static constexpr float kHintLabelX = 20.0f;
    static constexpr float kHintLabelY = 20.0f;
    static constexpr int kHintLabelTextSize = 18;

    static constexpr auto kMenuButtonPvPText = "Player vs Player\n    (Press '1')";
    static constexpr auto kMenuButtonPvAIText = "Player vs Bot\n  (Press '2')";
    static constexpr float kButtonWidth = 200.0f;
    static constexpr float kButtonHeight = 120.0f;
    static constexpr float kButtonSpacing = 100.0f;
    static constexpr float kButtonMenuYOffset = 20.0f;
    static constexpr int kButtonTextSize = 24;
    static constexpr float kButtonOutlineThickness = 3.0f;

    static constexpr float kPauseOverlayWidth = 600.0f;
    static constexpr float kPauseOverlayHeight = 200.0f;

    static constexpr auto kPauseTitleText = "Paused";
    static constexpr float kPauseTitleOffsetX = 60.0f;
    static constexpr float kPauseTitleYOffset = 20.0f;
    static constexpr int kPauseTitleTextSize = 36;

    static constexpr auto kPauseButtonContinueText = "Continue (Space)";
    static constexpr auto kPauseButtonRestartText = "Restart (R)";
    static constexpr auto kPauseButtonMenuText = "Menu (M)";
    static constexpr auto kPauseButtonExitText = "Exit (Esc)";
    static constexpr float kPauseButtonWidth = 135.0f;
    static constexpr float kPauseButtonHeight = 50.0f;
    static constexpr float kPauseButtonSpacing = 12.0f;
    static constexpr int kPauseButtonTextSize = 15;
    static constexpr float kPausePadding = 12.0f;

    static constexpr int kPauseCanvasBgGrey = 80;
    static constexpr int kPauseButtonBgGrey = 50;
    static constexpr int kGreyColor = 150;

    float m_windowWidth = 800.0f;
    float m_windowHeight = 600.0f;

    ResourceManager &m_resourceMgr;

    const sf::Font *m_font = nullptr;

    std::unique_ptr<UICanvas> m_menuCanvas;
    std::unique_ptr<UICanvas> m_pauseCanvas;
    std::unique_ptr<UICanvas> m_gameCanvas;
    UILabel *m_scoreLabel = nullptr;
    UILabel *m_speedLabel = nullptr;
};
