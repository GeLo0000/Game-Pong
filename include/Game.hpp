#pragma once

#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();

private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;
};
