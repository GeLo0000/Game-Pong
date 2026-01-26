#pragma once

#include <SFML/Window/Event.hpp>
#include <map>
#include <vector>

enum class GameAction {
    None,
    Quit,
    StartPvP,
    StartPvAI,
    PauseToggle,
    Restart,
    BackToMenu,
    MoveLeftPaddleUp,
    MoveLeftPaddleDown,
    MoveRightPaddleUp,
    MoveRightPaddleDown
};

class InputHandler {
  public:
    InputHandler();
    ~InputHandler() = default;

    GameAction getActionFromKey(const sf::Event::KeyPressed &keyEvent) const;
    bool isActionActive(GameAction action) const;

  private:
    std::map<sf::Keyboard::Scancode, GameAction> m_keyBindings;
    std::map<GameAction, sf::Keyboard::Scancode> m_actionBindings;
};
