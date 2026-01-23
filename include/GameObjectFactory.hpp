#pragma once

#include "Ball.hpp"
#include "Paddle.hpp"
#include <memory>

class GameObjectFactory {
  public:
    GameObjectFactory() = delete;

    static std::unique_ptr<Paddle> createPaddle(float x, float y, float width, float height,
                                                float windowHeight, bool isAI = false);

    static std::unique_ptr<Ball> createBall(float x, float y, float radius, float windowWidth,
                                            float windowHeight);
};
