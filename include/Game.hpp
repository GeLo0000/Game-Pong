#pragma once

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

    void onInputEvent(const Event &event);

  private:
    float m_windowWidth;
    float m_windowHeight;

    sf::RenderWindow m_window;
    sf::Clock m_clock;

    std::unique_ptr<Paddle> m_leftPaddle;
    std::unique_ptr<Paddle> m_rightPaddle;
    std::unique_ptr<Ball> m_ball;

    std::unique_ptr<UIManager> m_uiManager;
    std::unique_ptr<InputHandler> m_inputHandler;
    std::unique_ptr<CollisionHandler> m_collisionHandler;

    GameState m_currentState;
};
