#pragma once

#include "Ball.hpp"
#include "Paddle.hpp"
#include <memory>

class GameObjectFactory {
  public:
    static GameObjectFactory &instance();

    std::unique_ptr<Paddle> createPaddle(float x, float y, float width, float height,
                                         float windowHeight, bool isAI = false);

    std::unique_ptr<Ball> createBall(float x, float y, float radius, float windowWidth,
                                     float windowHeight);

  private:
    GameObjectFactory() = default;
    GameObjectFactory(const GameObjectFactory &) = delete;
    GameObjectFactory &operator=(const GameObjectFactory &) = delete;
};
