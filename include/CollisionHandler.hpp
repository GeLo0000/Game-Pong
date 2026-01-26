#pragma once

#include "Ball.hpp"
#include "EventManager.hpp"
#include "Paddle.hpp"
#include <SFML/Graphics.hpp>

class CollisionHandler {
  public:
    CollisionHandler(EventManager &eventMgr);
    ~CollisionHandler() = default;

    void handleCollisions(Ball &ball, Paddle &leftPaddle, Paddle &rightPaddle,
                          const sf::Vector2f &windowSize);

  private:
    void handleWallCollision(Ball &ball, const sf::Vector2f &windowSize);
    void handlePaddleCollision(Ball &ball, Paddle &paddle);
    void handleGoal(Ball &ball, const sf::Vector2f &windowSize);

    EventManager &m_eventMgr;
};
