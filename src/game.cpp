#include "game.h"

Game::Game(unsigned int width, unsigned int height)
    : m_window(width, height, "Pong Game"),
      m_playerPaddle(30.0f, (height / 2.0f) - 50.0f)
{
}

void Game::run()
{
    while (m_window.isOpen())
    {
        processEvents();
        m_input.update(m_inputState);
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
    if (m_inputState.quit)
    {
        m_window.close();
    }

    // Player paddle movement
    const float paddleSpeed = 6.0f;
    
    if (m_inputState.moveUp)
    {
        m_playerPaddle.moveUp(paddleSpeed, 0.0f);
    }
    if (m_inputState.moveDown)
    {
        m_playerPaddle.moveDown(paddleSpeed, static_cast<float>(m_window.getHeight()));
    }
}

void Game::render()
{
    m_window.clear();
    m_playerPaddle.draw(*m_window.getRenderWindow());
    m_window.display();
}
