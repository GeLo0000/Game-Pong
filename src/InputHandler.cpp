#include "InputHandler.hpp"

#include "Game.hpp"

void InputHandler::handleKeyPress(const sf::Event::KeyPressed &key, GameState currentState,
                                  EventManager &eventMgr) {
    if (key.scancode == sf::Keyboard::Scancode::Escape) {
        eventMgr.emit({EventType::INPUT_CLOSE_GAME});
        return;
    }

    if (currentState == GameState::MENU) {
        if (key.scancode == sf::Keyboard::Scancode::Num1 ||
            key.scancode == sf::Keyboard::Scancode::Numpad1) {
            eventMgr.emit({EventType::INPUT_START_PVP});
        } else if (key.scancode == sf::Keyboard::Scancode::Num2 ||
                   key.scancode == sf::Keyboard::Scancode::Numpad2) {
            eventMgr.emit({EventType::INPUT_START_PVAI});
        }
        return;
    }

    if (currentState == GameState::PLAYING || currentState == GameState::PAUSED) {
        if (key.scancode == sf::Keyboard::Scancode::Space) {
            if (currentState == GameState::PLAYING) {
                eventMgr.emit({EventType::INPUT_PAUSE});
            } else if (currentState == GameState::PAUSED) {
                eventMgr.emit({EventType::INPUT_RESUME});
            }
        } else if (key.scancode == sf::Keyboard::Scancode::R) {
            eventMgr.emit({EventType::INPUT_RESTART});
        } else if (key.scancode == sf::Keyboard::Scancode::M) {
            eventMgr.emit({EventType::INPUT_BACK_TO_MENU});
        }
    }
}
