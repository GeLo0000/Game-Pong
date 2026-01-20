#include "Game.hpp"
#include "AudioManager.hpp"
#include "EventManager.hpp"
#include "GameMode.hpp"
#include "GameObjectFactory.hpp"
#include "ResourceManager.hpp"
#include "ScoreManager.hpp"
#include <iostream>
#include <string>

// Initialize game window and create game objects
Game::Game()
    : m_windowWidth(800.0f), m_windowHeight(600.0f),
      m_window(sf::VideoMode({static_cast<unsigned int>(m_windowWidth),
                              static_cast<unsigned int>(m_windowHeight)}),
               "Pong Game"),
      m_currentState(GameState::MENU) {
    m_window.setFramerateLimit(144);

    // Initialize managers that need subscriptions
    AudioManager::instance();

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

    // Preload assets
    ResourceManager::instance().loadFont("main_font",
                                         "assets/fonts/Roboto-Regular.ttf");

    // Create game objects using factory
    auto &factory = GameObjectFactory::instance();
    const float paddleWidth = 15.0f;
    const float paddleHeight = 100.0f;
    m_leftPaddle =
        factory.createPaddle(50.0f, m_windowHeight / 2.0f, paddleWidth,
                             paddleHeight, m_windowHeight);

    // Create right paddle
    m_rightPaddle = factory.createPaddle(m_windowWidth - 50.0f - paddleWidth,
                                         m_windowHeight / 2.0f, paddleWidth,
                                         paddleHeight, m_windowHeight, true);

    // Create ball in center
    const float ballRadius = 10.0f;
    m_ball = factory.createBall(m_windowWidth / 2.0f, m_windowHeight / 2.0f,
                                ballRadius, m_windowWidth, m_windowHeight);

    // Load font via resource manager
    const sf::Font *font = ResourceManager::instance().getFont("main_font");
    if (!font) {
        std::cerr << "Warning: Could not load font\n";
    }

    m_scoreText = sf::Text(*font);
    m_scoreText->setCharacterSize(30);
    m_scoreText->setFillColor(sf::Color::White);
    m_scoreText->setPosition({m_windowWidth / 2.0f - 50.0f, 20.0f});

    // Initialize ScoreManager
    ScoreManager::instance();

    // Pause overlay text
    m_pausedText = sf::Text(*font);
    m_pausedText->setString("PAUSED");
    m_pausedText->setCharacterSize(40);
    m_pausedText->setFillColor(sf::Color::White);
    m_pausedText->setPosition(
        {m_windowWidth / 2.0f - 80.0f, m_windowHeight / 2.0f - 20.0f});

    // Menu text
    m_menuText = sf::Text(*font);
    m_menuText->setString(
        "PONG\n\n1 - PvP (W/S vs Up/Down)\n2 - PvAI (W/S vs AI)\nESC - Quit");
    m_menuText->setCharacterSize(26);
    m_menuText->setFillColor(sf::Color::White);
    m_menuText->setPosition({80.0f, 120.0f});
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
                continue;
            }

            // Menu selection
            if (m_currentState == GameState::MENU) {
                if (kp->scancode == sf::Keyboard::Scancode::Num1 ||
                    kp->scancode == sf::Keyboard::Scancode::Numpad1) {
                    GameModeManager::instance().selectMode(ModeType::PvP);
                    ScoreManager::instance().reset();
                    m_ball->reset();
                    m_currentState = GameState::PLAYING;
                    AudioManager::instance().playBackgroundMusic(
                        "assets/audio/background.ogg");
                } else if (kp->scancode == sf::Keyboard::Scancode::Num2 ||
                           kp->scancode == sf::Keyboard::Scancode::Numpad2) {
                    GameModeManager::instance().selectMode(ModeType::PvAI);
                    ScoreManager::instance().reset();
                    m_ball->reset();
                    m_currentState = GameState::PLAYING;
                    AudioManager::instance().playBackgroundMusic(
                        "assets/audio/background.ogg");
                }
                continue;
            }

            // Toggle pause in gameplay
            if (kp->scancode == sf::Keyboard::Scancode::Space &&
                m_currentState != GameState::MENU) {
                if (m_currentState == GameState::PLAYING) {
                    m_currentState = GameState::PAUSED;
                    EventManager::instance().emit(
                        {EventType::GAME_PAUSED, "paused"});
                } else if (m_currentState == GameState::PAUSED) {
                    m_currentState = GameState::PLAYING;
                    EventManager::instance().emit(
                        {EventType::GAME_RESUMED, "resumed"});
                }
            }
        }
    }
}

// Update game logic
void Game::update(float deltaTime) {
    // Skip updates while paused or in menu/game over states
    if (m_currentState == GameState::PAUSED ||
        m_currentState == GameState::MENU ||
        m_currentState == GameState::GAME_OVER) {
        return;
    }

    // Delegate paddle control to the active game mode
    if (auto *mode = GameModeManager::instance().currentMode()) {
        mode->update(deltaTime, *m_ball, *m_leftPaddle, *m_rightPaddle);
    } else {
        // Fallback to PvAI controls if no mode is set
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
            m_leftPaddle->moveUp();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) {
            m_leftPaddle->moveDown();
        }
        m_leftPaddle->update(deltaTime);

        const float ballCenterY =
            m_ball->getBounds().position.y + m_ball->getBounds().size.y / 2.0f;
        m_rightPaddle->updateAI(ballCenterY, deltaTime);
    }

    m_ball->update(deltaTime);

    handleCollisions();
}

// Render all game objects
void Game::render() {
    m_window.clear(sf::Color::Black);

    // Menu screen
    if (m_currentState == GameState::MENU) {
        if (m_menuText) {
            m_window.draw(*m_menuText);
        }
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

    // Update and draw score
    if (m_scoreText) {
        const int leftScore = ScoreManager::instance().getLeftScore();
        const int rightScore = ScoreManager::instance().getRightScore();
        m_scoreText->setString(std::to_string(leftScore) + " : " +
                               std::to_string(rightScore));
        m_window.draw(*m_scoreText);
    }

    // Draw pause text if paused
    if (m_currentState == GameState::PAUSED && m_pausedText) {
        m_window.draw(*m_pausedText);
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
        pos.x =
            leftBounds.position.x + leftBounds.size.x; // place next to paddle
        m_ball->setPosition(pos);
        m_ball->setVelocity(std::abs(velocity.x), velocity.y);
        m_ball->increaseSpeed();
        EventManager::instance().emit({EventType::PADDLE_HIT, "left paddle"});
        return;
    }

    const auto rightBounds = m_rightPaddle->getBounds();
    if (rightBounds.findIntersection(ballBounds).has_value()) {
        auto pos = ballBounds.position;
        pos.x =
            rightBounds.position.x - ballBounds.size.x; // place next to paddle
        m_ball->setPosition(pos);
        m_ball->setVelocity(std::abs(velocity.x) * -1.0f, velocity.y);
        m_ball->increaseSpeed();
        EventManager::instance().emit({EventType::PADDLE_HIT, "right paddle"});
    }
}
