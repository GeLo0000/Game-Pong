#pragma once

#include "Ball.hpp"
#include "EventManager.hpp"
#include "Paddle.hpp"
#include <SFML/Graphics.hpp>

class CollisionHandler {
  public:
    CollisionHandler(EventManager &eventMgr);

    void handleCollisions(Ball &ball, Paddle &leftPaddle, Paddle &rightPaddle,
                          const sf::Vector2f &windowSize);

  private:
    bool handleWallCollision(Ball &ball, const sf::Vector2f &windowSize);
    bool handlePaddleCollision(Ball &ball, Paddle &paddle);
    bool handleGoal(Ball &ball, const sf::Vector2f &windowSize);

    EventManager &m_eventMgr;
};
