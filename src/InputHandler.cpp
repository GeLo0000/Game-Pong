#include "InputHandler.hpp"

#include "Game.hpp"

bool InputHandler::handleKeyPress(const sf::Event::KeyPressed &key,
                                  GameState &state, Ball &ball) {
    if (key.scancode == sf::Keyboard::Scancode::Escape) {
        return true; // Close window
    }

    return handleGameplayKeyPress(key, state, ball);
}

bool InputHandler::handleMenuInput(const sf::Event::KeyPressed &key,
                                   Ball &ball) {
    if (key.scancode == sf::Keyboard::Scancode::Num1 ||
        key.scancode == sf::Keyboard::Scancode::Numpad1) {
        GameModeManager::instance().selectMode(ModeType::PvP);
        ScoreManager::instance().reset();
        ball.reset();
        return true; // Start game
    } else if (key.scancode == sf::Keyboard::Scancode::Num2 ||
               key.scancode == sf::Keyboard::Scancode::Numpad2) {
        GameModeManager::instance().selectMode(ModeType::PvAI);
        ScoreManager::instance().reset();
        ball.reset();
        return true; // Start game
    }
    return false;
}

bool InputHandler::handleGameplayKeyPress(const sf::Event::KeyPressed &key,
                                          GameState &state, Ball &ball) {
    // Space: toggle pause/resume
    if (key.scancode == sf::Keyboard::Scancode::Space) {
        if (state == GameState::PLAYING) {
            state = GameState::PAUSED;
            EventManager::instance().emit({EventType::GAME_PAUSED, "paused"});
        } else if (state == GameState::PAUSED) {
            state = GameState::PLAYING;
            EventManager::instance().emit({EventType::GAME_RESUMED, "resumed"});
        }
        return false;
    }

    // R: restart round (reset score and ball, continue playing)
    if (key.scancode == sf::Keyboard::Scancode::R) {
        ScoreManager::instance().reset();
        ball.reset();
        state = GameState::PLAYING;
        EventManager::instance().emit({EventType::GAME_RESUMED, "restarted"});
        return false;
    }

    // M: back to main menu
    if (key.scancode == sf::Keyboard::Scancode::M) {
        ScoreManager::instance().reset();
        ball.reset();
        state = GameState::MENU;
        EventManager::instance().emit({EventType::GAME_PAUSED, "menu"});
        return false;
    }

    return false;
}

void InputHandler::handleGameplayInput(float deltaTime, Paddle &leftPaddle,
                                       Paddle &rightPaddle, Ball &ball) {
    if (auto *mode = GameModeManager::instance().currentMode()) {
        mode->update(deltaTime, ball, leftPaddle, rightPaddle);
    }
}
