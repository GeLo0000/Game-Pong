#pragma once

#include "EventManager.hpp"
#include <SFML/Window/Event.hpp>

enum class GameState;

// Handles keyboard input and emits events
class InputHandler {
  public:
    InputHandler() = default;
    ~InputHandler() = default;

    // Process key press events and emit appropriate events
    void handleKeyPress(const sf::Event::KeyPressed &key, GameState currentState);
};
