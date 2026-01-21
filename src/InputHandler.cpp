#include "InputHandler.hpp"

#include "Game.hpp"

void InputHandler::handleKeyPress(const sf::Event::KeyPressed &key, GameState currentState) {
    auto &eventMgr = EventManager::instance();

    // Global key: Escape closes the game
    if (key.scancode == sf::Keyboard::Scancode::Escape) {
        eventMgr.emit({EventType::INPUT_CLOSE_GAME, "escape"});
        return;
    }

    // Menu state: handle mode selection
    if (currentState == GameState::MENU) {
        if (key.scancode == sf::Keyboard::Scancode::Num1 ||
            key.scancode == sf::Keyboard::Scancode::Numpad1) {
            eventMgr.emit({EventType::INPUT_START_PVP, "pvp"});
        } else if (key.scancode == sf::Keyboard::Scancode::Num2 ||
                   key.scancode == sf::Keyboard::Scancode::Numpad2) {
            eventMgr.emit({EventType::INPUT_START_PVAI, "pvai"});
        }
        return;
    }

    // Playing/Paused state: handle gameplay keys
    if (currentState == GameState::PLAYING || currentState == GameState::PAUSED) {
        // Space: toggle pause/resume
        if (key.scancode == sf::Keyboard::Scancode::Space) {
            if (currentState == GameState::PLAYING) {
                eventMgr.emit({EventType::INPUT_PAUSE, "pause"});
            } else if (currentState == GameState::PAUSED) {
                eventMgr.emit({EventType::INPUT_RESUME, "resume"});
            }
        }
        // R: restart round
        else if (key.scancode == sf::Keyboard::Scancode::R) {
            eventMgr.emit({EventType::INPUT_RESTART, "restart"});
        }
        // M: back to main menu
        else if (key.scancode == sf::Keyboard::Scancode::M) {
            eventMgr.emit({EventType::INPUT_BACK_TO_MENU, "menu"});
        }
    }
}
