#pragma once

#include "Ball.hpp"
#include "EventManager.hpp"
#include "GameMode.hpp"
#include "Paddle.hpp"
#include "ScoreManager.hpp"
#include <SFML/Window/Event.hpp>

enum class GameState;

// Handles keyboard input and menu interactions
class InputHandler {
  public:
    InputHandler() = default;
    ~InputHandler() = default;

    // Process key press events; returns true if should close window
    bool handleCloseGameKey(const sf::Event::KeyPressed &key);

    // Process menu input; returns true if game should start
    bool handleMenuInput(const sf::Event::KeyPressed &key, Ball &ball);

    // Process gameplay-specific key presses (pause, restart, menu)
    bool handleGameplayKeyPress(const sf::Event::KeyPressed &key, GameState &state, Ball &ball);
};
