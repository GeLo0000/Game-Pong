#include "GameObjectFactory.hpp"

GameObjectFactory &GameObjectFactory::instance() {
    static GameObjectFactory inst;
    return inst;
}

std::unique_ptr<Paddle> GameObjectFactory::createPaddle(float x, float y, float width, float height,
                                                        float windowHeight, bool isAI) {
    return std::make_unique<Paddle>(x, y, width, height, windowHeight, isAI);
}

std::unique_ptr<Ball> GameObjectFactory::createBall(float x, float y, float radius,
                                                    float windowWidth, float windowHeight) {
    return std::make_unique<Ball>(x, y, radius, windowWidth, windowHeight);
}
