#include "Game.hpp"
#include "AudioManager.hpp"
#include "EventManager.hpp"
#include "GameMode.hpp"
#include "GameObjectFactory.hpp"
#include "ResourceManager.hpp"
#include "ScoreManager.hpp"
#include <iostream>
#include <string>

// Initialize game window and components
Game::Game()
    : m_windowWidth(800.0f), m_windowHeight(600.0f),
      m_window(sf::VideoMode({static_cast<unsigned int>(m_windowWidth),
                              static_cast<unsigned int>(m_windowHeight)}),
               "Pong Game"),
      m_currentState(GameState::MENU) {
    m_window.setFramerateLimit(144);

    initializeManagers();
    loadResources();
    createGameObjects();
    initializeComponents();
}

Game::~Game() = default;

// Initialize singleton managers
void Game::initializeManagers() { AudioManager::instance(); }

// Load fonts and other assets
void Game::loadResources() {
    ResourceManager::instance().loadFont("main_font", "assets/fonts/Roboto-Regular.ttf");
}

// Create game objects using factory
void Game::createGameObjects() {
    auto &factory = GameObjectFactory::instance();
    const float paddleWidth = 15.0f;
    const float paddleHeight = 100.0f;

    m_leftPaddle = factory.createPaddle(50.0f, m_windowHeight / 2.0f, paddleWidth, paddleHeight,
                                        m_windowHeight);

    m_rightPaddle = factory.createPaddle(m_windowWidth - 50.0f - paddleWidth, m_windowHeight / 2.0f,
                                         paddleWidth, paddleHeight, m_windowHeight, true);

    const float ballRadius = 10.0f;
    m_ball = factory.createBall(m_windowWidth / 2.0f, m_windowHeight / 2.0f, ballRadius,
                                m_windowWidth, m_windowHeight);
}

// Initialize component managers
void Game::initializeComponents() {
    m_uiManager = std::make_unique<UIManager>(m_windowWidth, m_windowHeight);
    m_uiManager->loadFont(ResourceManager::instance().getFont("main_font"));
    m_inputHandler = std::make_unique<InputHandler>();
    m_collisionHandler = std::make_unique<CollisionHandler>();
}

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
            // Menu input handling
            if (m_currentState == GameState::MENU) {
                if (m_inputHandler->handleMenuInput(*kp, *m_ball)) {
                    m_currentState = GameState::PLAYING;
                    AudioManager::instance().playBackgroundMusic("assets/audio/background.ogg");
                }
                // continue;
            }

            // Gameplay input handling (pause/resume, restart, menu)
            if (m_inputHandler->handleKeyPress(*kp, m_currentState, *m_ball)) {
                m_window.close();
            }
        }
    }
}

// Update game logic
void Game::update(float deltaTime) {
    // Skip updates while paused or in menu
    if (m_currentState == GameState::PAUSED || m_currentState == GameState::MENU) {
        return;
    }

    // Delegate paddle control to the active game mode
    auto *mode = GameModeManager::instance().currentMode();
    mode->update(deltaTime, *m_ball, *m_leftPaddle, *m_rightPaddle);

    m_ball->update(deltaTime);

    handleCollisions();
}

// Render all game objects
void Game::render() {
    m_window.clear(sf::Color::Black);

    // Menu screen
    if (m_currentState == GameState::MENU) {
        m_uiManager->renderMenu(m_window);
        m_window.display();
        return;
    }

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

    // Render sscore and pause overlay
    m_uiManager->renderGameUI(m_window, m_ball->getVelocity());

    if (m_currentState == GameState::PAUSED) {
        m_uiManager->renderPause(m_window);
    }

    m_window.display();
}

// Collision handling: paddles, walls, goals
void Game::handleCollisions() {
    m_collisionHandler->handleCollisions(*m_ball, *m_leftPaddle, *m_rightPaddle,
                                         {m_windowWidth, m_windowHeight});
}
