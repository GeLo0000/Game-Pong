#pragma once

#include <SFML/Window/Event.hpp>
#include <map>

enum class GameAction {
    None,
    Quit,
    StartPvP,
    StartPvAI,
    PauseToggle,
    Restart,
    BackToMenu
};

class InputHandler {
  public:
    InputHandler();
    ~InputHandler() = default;

    GameAction getActionFromKey(const sf::Event::KeyPressed &keyEvent) const;

  private:
    std::map<sf::Keyboard::Scancode, GameAction> m_keyBindings;
};
