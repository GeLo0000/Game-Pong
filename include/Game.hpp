#pragma once

#include "AudioManager.hpp"
#include "Ball.hpp"
#include "CollisionHandler.hpp"
#include "InputHandler.hpp"
#include "Paddle.hpp"
#include "UIManager.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

enum class GameState { MENU, PLAYING, PAUSED };

class Game {
  public:
    Game();
    ~Game();
    void run();

  private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void handleCollisions();

    void createGameObjects();
    void initializeComponents();
    void subscribeToEvents();

    void onStartPvP();
    void onStartPvAI();
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

    std::unique_ptr<AudioManager> m_audioManager;
    std::unique_ptr<UIManager> m_uiManager;
    std::unique_ptr<InputHandler> m_inputHandler;
    std::unique_ptr<CollisionHandler> m_collisionHandler;

    GameState m_currentState;
};
