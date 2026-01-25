#pragma once

#include "Ball.hpp"
#include "Paddle.hpp"
#include "AIPaddle.hpp"
#include <memory>

class GameObjectFactory {
  public:
    GameObjectFactory() = delete;
    static std::unique_ptr<Ball> createBall(float x, float y, float radius, float windowWidth,
                                            float windowHeight);

    static std::unique_ptr<Paddle> createPaddle(float x, float y, float width, float height,
                                                float windowHeight);

    static std::unique_ptr<AIPaddle> createAIPaddle(float x, float y, float width, float height,
                                                    float windowHeight, const Ball& ball);
};
