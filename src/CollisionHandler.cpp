#include "CollisionHandler.hpp"

#include "Ball.hpp"
#include "EventManager.hpp"
#include "Paddle.hpp"

void CollisionHandler::handleCollisions(Ball &ball, Paddle &leftPaddle, Paddle &rightPaddle,
                                        const sf::Vector2f &windowSize) {
    handleWallCollision(ball, windowSize);
    handleGoal(ball, windowSize);
    handlePaddleCollision(ball, leftPaddle);
    handlePaddleCollision(ball, rightPaddle);
}

void CollisionHandler::handleWallCollision(Ball &ball, const sf::Vector2f &windowSize) {
    auto ballBounds = ball.getBounds();
    const auto velocity = ball.getVelocity();

    if (ballBounds.position.y < 0.0f) {
        ballBounds.position.y = 0.0f;
        ball.setPosition(ballBounds.position);
        ball.setVelocity(velocity.x, -velocity.y);
        EventManager::instance().emit({EventType::WALL_HIT});
    } else if (ballBounds.position.y + ballBounds.size.y > windowSize.y) {
        ballBounds.position.y = windowSize.y - ballBounds.size.y;
        ball.setPosition(ballBounds.position);
        ball.setVelocity(velocity.x, -velocity.y);
        EventManager::instance().emit({EventType::WALL_HIT});
    }
}

void CollisionHandler::handleGoal(Ball &ball, const sf::Vector2f &windowSize) {
    auto ballBounds = ball.getBounds();

    if (ballBounds.position.x + ballBounds.size.x < 0.0f) {
        EventManager::instance().emit({EventType::GOAL_SCORED_LEFT});
        ball.reset();
        return;
    }

    if (ballBounds.position.x > windowSize.x) {
        EventManager::instance().emit({EventType::GOAL_SCORED_RIGHT});
        ball.reset();
    }
}

void CollisionHandler::handlePaddleCollision(Ball &ball, Paddle &paddle) {
    auto ballBounds = ball.getBounds();
    const auto velocity = ball.getVelocity();
    const auto paddleBounds = paddle.getBounds();

    if (paddleBounds.findIntersection(ballBounds).has_value()) {
        auto pos = ballBounds.position;

        if (paddleBounds.position.x < ballBounds.position.x) {
            pos.x = paddleBounds.position.x + paddleBounds.size.x;
            ball.setPosition(pos);
            ball.setVelocity(std::abs(velocity.x), velocity.y);
        } else {
            pos.x = paddleBounds.position.x - ballBounds.size.x;
            ball.setPosition(pos);
            ball.setVelocity(std::abs(velocity.x) * -1.0f, velocity.y);
        }

        ball.increaseSpeed();
        EventManager::instance().emit({EventType::PADDLE_HIT});
    }
}
