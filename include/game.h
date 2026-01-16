#ifndef GAME_H
#define GAME_H

#include "window.h"
#include "input_handler.h"
#include "paddle.h"
#include <SFML/Graphics.hpp>

// Core game class that owns the main loop
class Game
{
public:
    Game(unsigned int width = 800, unsigned int height = 600);

    // Run the main game loop
    void run();

private:
    void processEvents();
    void update();
    void render();

    Window m_window;
    InputHandler m_input;
    InputState m_inputState;
    Paddle m_playerPaddle;
};

#endif // GAME_H
