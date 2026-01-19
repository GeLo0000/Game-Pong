#pragma once

#include "Ball.hpp"
#include "Paddle.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

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
};
