#include "InputHandler.hpp"

#include "Game.hpp"

bool InputHandler::handleKeyPress(const sf::Event::KeyPressed &key, GameState &state, Ball &ball) {
    if (key.scancode == sf::Keyboard::Scancode::Escape) {
        return true; // Close window
    }

    return handleGameplayKeyPress(key, state, ball);
}

bool InputHandler::handleMenuInput(const sf::Event::KeyPressed &key, Ball &ball) {
    // Map keys 1 and 2 (or numpad) to modes
    std::optional<ModeType> mode;

    if (key.scancode == sf::Keyboard::Scancode::Num1 ||
        key.scancode == sf::Keyboard::Scancode::Numpad1) {
        mode = ModeType::PvP;
    } else if (key.scancode == sf::Keyboard::Scancode::Num2 ||
               key.scancode == sf::Keyboard::Scancode::Numpad2) {
        mode = ModeType::PvAI;
    }

    if (mode.has_value()) {
        GameModeManager::instance().selectMode(mode.value());
        ScoreManager::instance().reset();
        ball.reset();
        return true; // Start game
    }

    return false;
}

bool InputHandler::handleGameplayKeyPress(const sf::Event::KeyPressed &key, GameState &state,
                                          Ball &ball) {
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
