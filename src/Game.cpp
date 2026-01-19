#include "Game.hpp"

// Initialize game window and create game objects
Game::Game()
    : m_windowWidth(800.0f), m_windowHeight(600.0f),
      m_window(sf::VideoMode({static_cast<unsigned int>(m_windowWidth),
                              static_cast<unsigned int>(m_windowHeight)}),
               "Pong Game") {
    m_window.setFramerateLimit(144);

    // Create left paddle
    const float paddleWidth = 15.0f;
    const float paddleHeight = 100.0f;
    m_leftPaddle =
        std::make_unique<Paddle>(50.0f, m_windowHeight / 2.0f, paddleWidth,
                                 paddleHeight, m_windowHeight);

    // Create right paddle
    m_rightPaddle =
        std::make_unique<Paddle>(m_windowWidth - 50.0f - paddleWidth,
                                 m_windowHeight / 2.0f, paddleWidth,
                                 paddleHeight, m_windowHeight);

    // Create ball in center
    const float ballRadius = 10.0f;
    m_ball = std::make_unique<Ball>(m_windowWidth / 2.0f, m_windowHeight / 2.0f,
                                    ballRadius, m_windowWidth, m_windowHeight);
}

Game::~Game() = default;

// Main game loop
void Game::run() {
    while (m_window.isOpen()) {
        float dt = m_clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

// Handle window events
void Game::processEvents() {
    while (const std::optional ev = m_window.pollEvent()) {
        if (ev->is<sf::Event::Closed>()) {
            m_window.close();
        } else if (const auto *kp = ev->getIf<sf::Event::KeyPressed>()) {
            if (kp->scancode == sf::Keyboard::Scancode::Escape) {
                m_window.close();
            }
        }
    }
}

// Update game logic
void Game::update(float deltaTime) {
    // Handle continuous input for left paddle (W/S)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
        m_leftPaddle->moveUp();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) {
        m_leftPaddle->moveDown();
    }

    // Handle continuous input for right paddle (arrow keys)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up)) {
        m_rightPaddle->moveUp();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down)) {
        m_rightPaddle->moveDown();
    }

    m_leftPaddle->update(deltaTime);
    m_rightPaddle->update(deltaTime);
    m_ball->update(deltaTime);
}

// Render all game objects
void Game::render() {
    m_window.clear(sf::Color::Black);

    // Draw game objects
    if (m_leftPaddle) {
        m_leftPaddle->draw(m_window);
    }
    if (m_rightPaddle) {
        m_rightPaddle->draw(m_window);
    }
    if (m_ball) {
        m_ball->draw(m_window);
    }

    m_window.display();
}
