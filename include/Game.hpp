#pragma once

#include "AudioManager.hpp"
#include "Ball.hpp"
#include "CollisionHandler.hpp"
#include "EventManager.hpp"
#include "InputHandler.hpp"
#include "Paddle.hpp"
#include "ResourceManager.hpp"
#include "ScoreManager.hpp"
#include "UIManager.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

enum class GameState { MENU, PLAYING, PAUSED };
enum class GameType { NONE, PvP, PvAI };

class Game {
  public:
    Game();
    void run();

  private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void handleCollisions();
    void handleAction(GameAction action);

    void createGameObjects();
    void initializeComponents();
    void resetGame();

    void onStart(GameType type);
    void onPause();
    void onResume();
    void onRestart();
    void onBackToMenu();
    void onCloseGame();

  private:
    static constexpr float kWindowWidth = 800.0f;
    static constexpr float kWindowHeight = 600.0f;
    static constexpr int kFramerateLimit = 144;

    static constexpr float kPaddleWidth = 15.0f;
    static constexpr float kPaddleHeight = 100.0f;
    static constexpr float kPaddleLeftX = 50.0f;
    static constexpr float kPaddleRightXOffset = 50.0f;

    static constexpr float kBallRadius = 10.0f;

    static constexpr auto kWindowTitle = "Pong Game";

    sf::RenderWindow m_window;
    sf::Clock m_clock;

    std::unique_ptr<Paddle> m_leftPaddle;
    std::unique_ptr<Paddle> m_rightPaddle;
    std::unique_ptr<Ball> m_ball;

    EventManager &m_eventManager;
    ResourceManager &m_resourceManager;
    std::unique_ptr<AudioManager> m_audioManager;
    std::unique_ptr<UIManager> m_uiManager;
    std::unique_ptr<ScoreManager> m_scoreManager;
    std::unique_ptr<InputHandler> m_inputHandler;
    std::unique_ptr<CollisionHandler> m_collisionHandler;

    GameState m_currentState = GameState::MENU;
    GameType m_currentType = GameType::NONE;
};
