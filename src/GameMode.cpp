#include "GameMode.hpp"

#include "Ball.hpp"
#include "Paddle.hpp"
#include <SFML/Window/Keyboard.hpp>

GameModeManager &GameModeManager::instance() {
    static GameModeManager inst;
    return inst;
}

void GameModeManager::selectMode(ModeType type) {
    switch (type) {
    case ModeType::PvP:
        m_mode = std::make_unique<PvPMode>();
        break;
    case ModeType::PvAI:
        m_mode = std::make_unique<PvAIMode>();
        break;
    }
}

GameMode *GameModeManager::currentMode() { return m_mode.get(); }

void PvPMode::update(float deltaTime, Ball &ball, Paddle &left, Paddle &right) {
    // Left paddle controls (W/S)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
        left.moveUp();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) {
        left.moveDown();
    }

    // Right paddle controls (Up/Down)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up)) {
        right.moveUp();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down)) {
        right.moveDown();
    }

    left.update(deltaTime);
    right.update(deltaTime);
}

void PvAIMode::update(float deltaTime, Ball &ball, Paddle &left, Paddle &right) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
        left.moveUp();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) {
        left.moveDown();
    }

    left.update(deltaTime);

    const float ballCenterY = ball.getBounds().position.y + ball.getBounds().size.y / 2.0f;
    right.updateAI(ballCenterY, deltaTime);
}
