#pragma once

#include "Ball.hpp"
#include "Paddle.hpp"
#include "UIManager.hpp"
#include "InputHandler.hpp"
#include "CollisionHandler.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <optional>

// Game state enum
enum class GameState { MENU, PLAYING, PAUSED, GAME_OVER };

// Main game controller class
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

    // Initialization methods
    void initializeManagers();
    void setupEventListeners();
    void loadResources();
    void createGameObjects();
    void initializeComponents();

  private:
    // Window dimensions
    float m_windowWidth;
    float m_windowHeight;

    sf::RenderWindow m_window; // Main game window
    sf::Clock m_clock;         // Clock for delta time tracking

    // Game objects
    std::unique_ptr<Paddle> m_leftPaddle;
    std::unique_ptr<Paddle> m_rightPaddle;
    std::unique_ptr<Ball> m_ball;

    // Manager objects
    std::unique_ptr<UIManager> m_uiManager;
    std::unique_ptr<InputHandler> m_inputHandler;
    std::unique_ptr<CollisionHandler> m_collisionHandler;

    // Game state
    GameState m_currentState;
};
