#include "Game.hpp"

Game::Game()
    : m_window(sf::VideoMode({800u, 600u}), "Pong Game")
{
    m_window.setFramerateLimit(144);
}

void Game::run()
{
    while (m_window.isOpen())
    {
        float dt = m_clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents()
{
    while (const std::optional ev = m_window.pollEvent())
    {
        if (ev->is<sf::Event::Closed>())
        {
            m_window.close();
        }
        else if (const auto *kp = ev->getIf<sf::Event::KeyPressed>())
        {
            if (kp->scancode == sf::Keyboard::Scancode::Escape)
            {
                m_window.close();
            }
        }
    }

    // Also allow holding ESC to close quickly
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
    {
        m_window.close();
    }
}

void Game::update(float deltaTime)
{

}

void Game::render()
{
    m_window.clear(sf::Color::White);
    m_window.display();
}
