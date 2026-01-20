#pragma once

#include <SFML/Graphics.hpp>

class Ball;
class Paddle;

class CollisionHandler {
  public:
    CollisionHandler() = default;
    ~CollisionHandler() = default;

    void handleCollisions(Ball &ball, Paddle &leftPaddle, Paddle &rightPaddle,
                         const sf::Vector2f &windowSize);

  private:
    void handleWallCollision(Ball &ball, const sf::Vector2f &windowSize);
    void handlePaddleCollision(Ball &ball, Paddle &paddle);
    void handleGoal(Ball &ball, const sf::Vector2f &windowSize);
};
