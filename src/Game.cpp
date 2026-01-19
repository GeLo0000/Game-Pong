#include "Game.hpp"
#include "EventManager.hpp"
#include <iostream>

// Initialize game window and create game objects
Game::Game()
    : m_windowWidth(800.0f), m_windowHeight(600.0f),
      m_window(sf::VideoMode({static_cast<unsigned int>(m_windowWidth),
                              static_cast<unsigned int>(m_windowHeight)}),
               "Pong Game") {
    m_window.setFramerateLimit(60);

    // Subscribe to events for quick console verification
    EventManager::instance().subscribe(
        EventType::PADDLE_HIT, [](const Event &e) {
            std::cout << "Event: PADDLE_HIT (" << e.info << ")\n";
        });
    EventManager::instance().subscribe(EventType::WALL_HIT, [](const Event &e) {
        std::cout << "Event: WALL_HIT (" << e.info << ")\n";
    });
    EventManager::instance().subscribe(
        EventType::GOAL_SCORED, [](const Event &e) {
            std::cout << "Event: GOAL_SCORED (" << e.info << ")\n";
        });

    // Create left paddle
    const float paddleWidth = 15.0f;
    const float paddleHeight = 100.0f;
    m_leftPaddle =
        std::make_unique<Paddle>(50.0f, m_windowHeight / 2.0f, paddleWidth,
                                 paddleHeight, m_windowHeight);

    // Create right paddle
    m_rightPaddle = std::make_unique<Paddle>(
        m_windowWidth - 50.0f - paddleWidth, m_windowHeight / 2.0f, paddleWidth,
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

    handleCollisions();
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

// Collision handling: paddles, walls, goals
void Game::handleCollisions() {
    auto ballBounds = m_ball->getBounds();
    const auto velocity = m_ball->getVelocity();

    // Top/Bottom walls
    if (ballBounds.position.y < 0.0f) {
        ballBounds.position.y = 0.0f;
        m_ball->setPosition(ballBounds.position);
        m_ball->setVelocity(velocity.x, -velocity.y);
        EventManager::instance().emit({EventType::WALL_HIT, "top"});
    } else if (ballBounds.position.y + ballBounds.size.y > m_windowHeight) {
        ballBounds.position.y = m_windowHeight - ballBounds.size.y;
        m_ball->setPosition(ballBounds.position);
        m_ball->setVelocity(velocity.x, -velocity.y);
        EventManager::instance().emit({EventType::WALL_HIT, "bottom"});
    }

    // Left/Right goals
    if (ballBounds.position.x + ballBounds.size.x < 0.0f) {
        EventManager::instance().emit({EventType::GOAL_SCORED, "left wall"});
        m_ball->reset();
        return;
    }
    if (ballBounds.position.x > m_windowWidth) {
        EventManager::instance().emit({EventType::GOAL_SCORED, "right wall"});
        m_ball->reset();
        return;
    }

    // Paddle collisions (AABB via findIntersection)
    const auto leftBounds = m_leftPaddle->getBounds();
    if (leftBounds.findIntersection(ballBounds).has_value()) {
        auto pos = ballBounds.position;
        pos.x = leftBounds.position.x + leftBounds.size.x;
        m_ball->setPosition(pos);
        m_ball->setVelocity(std::abs(velocity.x), velocity.y);
        EventManager::instance().emit({EventType::PADDLE_HIT, "left paddle"});
        return;
    }

    const auto rightBounds = m_rightPaddle->getBounds();
    if (rightBounds.findIntersection(ballBounds).has_value()) {
        auto pos = ballBounds.position;
        pos.x = rightBounds.position.x - ballBounds.size.x;
        m_ball->setPosition(pos);
        m_ball->setVelocity(std::abs(velocity.x) * -1.0f, velocity.y);
        EventManager::instance().emit({EventType::PADDLE_HIT, "right paddle"});
    }
}
