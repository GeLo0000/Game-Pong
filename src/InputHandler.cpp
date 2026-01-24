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
}

GameAction InputHandler::getActionFromKey(const sf::Event::KeyPressed &keyEvent) const {
    auto it = m_keyBindings.find(keyEvent.scancode);
    if (it != m_keyBindings.end()) {
        return it->second;
    }
    return GameAction::None;
}
