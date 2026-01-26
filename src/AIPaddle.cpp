#include "AIPaddle.hpp"

AIPaddle::AIPaddle(float x, float y, float width, float height, float windowHeight,
                   const Ball &ball)
    : Paddle(x, y, width, height, windowHeight), m_ball(&ball) {}

void AIPaddle::update(float deltaTime) {
    const float ballCenterY = m_ball->getBounds().position.y + m_ball->getBounds().size.y * 0.5f;
    const float paddleCenterY = m_shape.getPosition().y + m_shape.getSize().y * 0.5f;

    if (ballCenterY < paddleCenterY - kAiDetectionThreshold) {
        Paddle::moveUp();
    } else if (ballCenterY > paddleCenterY + kAiDetectionThreshold) {
        Paddle::moveDown();
    }

    Paddle::update(deltaTime);
}
