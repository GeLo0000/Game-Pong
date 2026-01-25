#include "Game.hpp"
#include "AIPaddle.hpp"
#include "EventManager.hpp"
#include "GameObjectFactory.hpp"
#include "ResourceManager.hpp"
#include "ScoreManager.hpp"
#include <string>

Game::Game()
    : m_window(sf::VideoMode({static_cast<unsigned int>(kWindowWidth),
                              static_cast<unsigned int>(kWindowHeight)}),
               kWindowTitle),
      m_eventManager(EventManager::instance()), m_currentState(GameState::MENU),
      m_currentType(GameType::NONE) {
    m_window.setFramerateLimit(kFramerateLimit);

    initializeComponents();
}

Game::~Game() = default;

void Game::createGameObjects(GameType type) {
    m_ball = GameObjectFactory::createBall(kWindowWidth / 2.0f, kWindowHeight / 2.0f, kBallRadius,
                                           kWindowWidth, kWindowHeight);

    m_leftPaddle = GameObjectFactory::createPaddle(kPaddleLeftX, kWindowHeight / 2.0f, kPaddleWidth,
                                                   kPaddleHeight, kWindowHeight);

    if (type == GameType::PvAI) {
        m_rightPaddle = GameObjectFactory::createAIPaddle(
            kWindowWidth - kPaddleRightXOffset - kPaddleWidth, kWindowHeight / 2.0f, kPaddleWidth,
            kPaddleHeight, kWindowHeight, *m_ball);
    } else {
        m_rightPaddle = GameObjectFactory::createPaddle(
            kWindowWidth - kPaddleRightXOffset - kPaddleWidth, kWindowHeight / 2.0f, kPaddleWidth,
            kPaddleHeight, kWindowHeight);
    }
}

void Game::initializeComponents() {
    m_audioManager = std::make_unique<AudioManager>(ResourceManager::instance(), m_eventManager);
    m_uiManager =
        std::make_unique<UIManager>(kWindowWidth, kWindowHeight, ResourceManager::instance());
    m_inputHandler = std::make_unique<InputHandler>();
    m_collisionHandler = std::make_unique<CollisionHandler>(m_eventManager);
}

void Game::resetGame() {
    m_leftPaddle.reset();
    m_rightPaddle.reset();
    m_ball.reset();
    ScoreManager::instance().reset();
}

void Game::run() {
    while (m_window.isOpen()) {
        float dt = m_clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    while (const std::optional ev = m_window.pollEvent()) {
        if (ev->is<sf::Event::Closed>()) {
            m_window.close();
        } else if (const auto *kp = ev->getIf<sf::Event::KeyPressed>()) {
            GameAction action = m_inputHandler->getActionFromKey(*kp);
            handleAction(action);
        }
    }
}

void Game::handleAction(GameAction action) {
    switch (action) {
    case GameAction::Quit:
        onCloseGame();
        break;

    case GameAction::StartPvP:
        if (m_currentState == GameState::MENU) {
            onStart(GameType::PvP);
        }
        break;

    case GameAction::StartPvAI:
        if (m_currentState == GameState::MENU) {
            onStart(GameType::PvAI);
        }
        break;

    case GameAction::PauseToggle:
        if (m_currentState == GameState::PLAYING) {
            onPause();
        } else if (m_currentState == GameState::PAUSED) {
            onResume();
        }
        break;

    case GameAction::Restart:
        if (m_currentState == GameState::PLAYING || m_currentState == GameState::PAUSED) {
            onRestart();
        }
        break;

    case GameAction::BackToMenu:
        if (m_currentState == GameState::PLAYING || m_currentState == GameState::PAUSED) {
            onBackToMenu();
        }
        break;

    case GameAction::None:
    default:
        break;
    }
}

void Game::update(float deltaTime) {
    if (m_currentState == GameState::PAUSED || m_currentState == GameState::MENU) {
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
        m_leftPaddle->moveUp();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) {
        m_leftPaddle->moveDown();
    }

    if (m_currentType == GameType::PvP) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up)) {
            m_rightPaddle->moveUp();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down)) {
            m_rightPaddle->moveDown();
        }
    }

    m_leftPaddle->update(deltaTime);
    m_rightPaddle->update(deltaTime);

    m_ball->update(deltaTime);
    m_audioManager->update();

    handleCollisions();
}

void Game::render() {
    m_window.clear(sf::Color::Black);

    if (m_currentState == GameState::MENU) {
        m_uiManager->renderMenu(m_window);
        m_window.display();
        return;
    }

    if (m_leftPaddle) {
        m_leftPaddle->draw(m_window);
    }
    if (m_rightPaddle) {
        m_rightPaddle->draw(m_window);
    }
    if (m_ball) {
        m_ball->draw(m_window);
    }

    m_uiManager->renderGameUI(m_window, *m_ball, ScoreManager::instance());

    if (m_currentState == GameState::PAUSED) {
        m_uiManager->renderPause(m_window);
    }

    m_window.display();
}

void Game::handleCollisions() {
    m_collisionHandler->handleCollisions(*m_ball, *m_leftPaddle, *m_rightPaddle,
                                         {kWindowWidth, kWindowHeight});
}

void Game::onStart(GameType type) {
    resetGame();
    createGameObjects(type);
    m_currentType = type;
    m_currentState = GameState::PLAYING;
    m_eventManager.emit(EventType::GAME_START);
}

void Game::onPause() {
    m_currentState = GameState::PAUSED;
    m_eventManager.emit(EventType::GAME_PAUSE);
}

void Game::onResume() {
    m_currentState = GameState::PLAYING;
    m_eventManager.emit(EventType::GAME_RESUME);
}

void Game::onRestart() {
    m_ball->reset();
    ScoreManager::instance().reset();
    m_currentState = GameState::PLAYING;
    m_eventManager.emit(EventType::GAME_RESUME);
}

void Game::onBackToMenu() {
    resetGame();
    m_currentType = GameType::NONE;
    m_currentState = GameState::MENU;
    m_eventManager.emit(EventType::GAME_PAUSE);
}

void Game::onCloseGame() { m_window.close(); }
