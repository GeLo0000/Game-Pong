#pragma once

#include "Ball.hpp"
#include "Paddle.hpp"

class AIPaddle : public Paddle {
  public:
    AIPaddle(float x, float y, float width, float height, float windowHeight, const Ball &ball);

    void update(float deltaTime) override;

  private:
    static constexpr float kAiDetectionThreshold = 10.0f;

    const Ball *m_ball;
};
