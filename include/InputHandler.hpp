#pragma once

#include "EventManager.hpp"
#include <SFML/Window/Event.hpp>

enum class GameState;

class InputHandler {
  public:
    InputHandler() = default;
    ~InputHandler() = default;

    void handleKeyPress(const sf::Event::KeyPressed &key, GameState currentState);
};
