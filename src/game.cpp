#include "game.h"

Game::Game(unsigned int width, unsigned int height)
    : m_window(width, height, "Pong Game")
{
    // Temporary drawable to verify rendering
    m_ball.setRadius(20.f);
    m_ball.setFillColor(sf::Color::Green);
    m_ball.setPosition((width / 2.f) - m_ball.getRadius(), (height / 2.f) - m_ball.getRadius());
}

void Game::run()
{
    while (m_window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event{};
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }
    }
}

void Game::update()
{
    // Game logic will go here (movement, collisions, AI)
}

void Game::render()
{
    m_window.clear();
    m_window.draw(m_ball);
    m_window.display();
}
