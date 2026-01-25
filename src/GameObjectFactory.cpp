#include "GameObjectFactory.hpp"

std::unique_ptr<Ball> GameObjectFactory::createBall(float x, float y, float radius,
                                                    float windowWidth, float windowHeight) {
    return std::make_unique<Ball>(x, y, radius, windowWidth, windowHeight);
}

std::unique_ptr<Paddle> GameObjectFactory::createPaddle(float x, float y, float width, float height,
                                                        float windowHeight) {
    return std::make_unique<Paddle>(x, y, width, height, windowHeight);
}
std::unique_ptr<AIPaddle> GameObjectFactory::createAIPaddle(float x, float y, float width,
                                                          float height, float windowHeight,
                                                          const Ball& ball) {
    return std::make_unique<AIPaddle>(x, y, width, height, windowHeight, ball);
}