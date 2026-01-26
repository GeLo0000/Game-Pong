#include "InputHandler.hpp"

InputHandler::InputHandler() {
    m_keyBindings[sf::Keyboard::Scancode::Escape] = GameAction::Quit;
    m_keyBindings[sf::Keyboard::Scancode::Space] = GameAction::PauseToggle;
    m_keyBindings[sf::Keyboard::Scancode::R] = GameAction::Restart;
    m_keyBindings[sf::Keyboard::Scancode::M] = GameAction::BackToMenu;
    m_keyBindings[sf::Keyboard::Scancode::Num1] = GameAction::StartPvP;
    m_keyBindings[sf::Keyboard::Scancode::Numpad1] = GameAction::StartPvP;
    m_keyBindings[sf::Keyboard::Scancode::Num2] = GameAction::StartPvAI;
    m_keyBindings[sf::Keyboard::Scancode::Numpad2] = GameAction::StartPvAI;

    m_actionBindings[GameAction::MoveLeftPaddleUp] = sf::Keyboard::Scancode::W;
    m_actionBindings[GameAction::MoveLeftPaddleDown] = sf::Keyboard::Scancode::S;
    m_actionBindings[GameAction::MoveRightPaddleUp] = sf::Keyboard::Scancode::Up;
    m_actionBindings[GameAction::MoveRightPaddleDown] = sf::Keyboard::Scancode::Down;
}

GameAction InputHandler::getActionFromKey(const sf::Event::KeyPressed &keyEvent) const {
    auto it = m_keyBindings.find(keyEvent.scancode);
    if (it != m_keyBindings.end()) {
        return it->second;
    }
    return GameAction::None;
}

bool InputHandler::isActionActive(GameAction action) const {
    auto it = m_actionBindings.find(action);
    if (it != m_actionBindings.end()) {
        return sf::Keyboard::isKeyPressed(it->second);
    }
    return false;
}