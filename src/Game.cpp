#include "Game.hpp"
#include "AudioManager.hpp"
#include "EventManager.hpp"
#include "GameMode.hpp"
#include "GameObjectFactory.hpp"
#include "ResourceManager.hpp"
#include "ScoreManager.hpp"
#include <string>

Game::Game()
    : m_windowWidth(800.0f), m_windowHeight(600.0f),
      m_window(sf::VideoMode({static_cast<unsigned int>(m_windowWidth),
                              static_cast<unsigned int>(m_windowHeight)}),
               "Pong Game"),
      m_currentState(GameState::MENU) {
    m_window.setFramerateLimit(144);

    createGameObjects();
    initializeComponents();
    subscribeToEvents();
}

Game::~Game() = default;

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

void Game::initializeComponents() {
    AudioManager::instance();
    m_uiManager = std::make_unique<UIManager>(m_windowWidth, m_windowHeight);
    m_inputHandler = std::make_unique<InputHandler>();
    m_collisionHandler = std::make_unique<CollisionHandler>();
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
            m_inputHandler->handleKeyPress(*kp, m_currentState);
        }
    }
}

void Game::update(float deltaTime) {
    if (m_currentState == GameState::PAUSED || m_currentState == GameState::MENU) {
        return;
    }

    auto *mode = GameModeManager::instance().currentMode();
    mode->update(deltaTime, *m_ball, *m_leftPaddle, *m_rightPaddle);

    m_ball->update(deltaTime);

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

    m_uiManager->renderGameUI(m_window, m_ball->getVelocity());

    if (m_currentState == GameState::PAUSED) {
        m_uiManager->renderPause(m_window);
    }

    m_window.display();
}

void Game::handleCollisions() {
    m_collisionHandler->handleCollisions(*m_ball, *m_leftPaddle, *m_rightPaddle,
                                         {m_windowWidth, m_windowHeight});
}

void Game::subscribeToEvents() {
    auto &eventMgr = EventManager::instance();

    eventMgr.subscribe(EventType::INPUT_START_PVP, [this](const Event &e) { onInputEvent(e); });
    eventMgr.subscribe(EventType::INPUT_START_PVAI, [this](const Event &e) { onInputEvent(e); });
    eventMgr.subscribe(EventType::INPUT_PAUSE, [this](const Event &e) { onInputEvent(e); });
    eventMgr.subscribe(EventType::INPUT_RESUME, [this](const Event &e) { onInputEvent(e); });
    eventMgr.subscribe(EventType::INPUT_RESTART, [this](const Event &e) { onInputEvent(e); });
    eventMgr.subscribe(EventType::INPUT_BACK_TO_MENU, [this](const Event &e) { onInputEvent(e); });
    eventMgr.subscribe(EventType::INPUT_CLOSE_GAME, [this](const Event &e) { onInputEvent(e); });
}

void Game::onInputEvent(const Event &event) {
    switch (event.type) {
    case EventType::INPUT_START_PVP:
        GameModeManager::instance().selectMode(ModeType::PvP);
        ScoreManager::instance().reset();
        m_ball->reset();
        m_currentState = GameState::PLAYING;
        AudioManager::instance().playBackgroundMusic("assets/audio/background.ogg");
        break;

    case EventType::INPUT_START_PVAI:
        GameModeManager::instance().selectMode(ModeType::PvAI);
        ScoreManager::instance().reset();
        m_ball->reset();
        m_currentState = GameState::PLAYING;
        AudioManager::instance().playBackgroundMusic("assets/audio/background.ogg");
        break;

    case EventType::INPUT_PAUSE:
        m_currentState = GameState::PAUSED;
        EventManager::instance().emit({EventType::GAME_PAUSED, "paused"});
        break;

    case EventType::INPUT_RESUME:
        m_currentState = GameState::PLAYING;
        EventManager::instance().emit({EventType::GAME_RESUMED, "resumed"});
        break;

    case EventType::INPUT_RESTART:
        ScoreManager::instance().reset();
        m_ball->reset();
        m_currentState = GameState::PLAYING;
        EventManager::instance().emit({EventType::GAME_RESUMED, "restarted"});
        break;

    case EventType::INPUT_BACK_TO_MENU:
        ScoreManager::instance().reset();
        m_ball->reset();
        m_currentState = GameState::MENU;
        EventManager::instance().emit({EventType::GAME_PAUSED, "menu"});
        break;

    case EventType::INPUT_CLOSE_GAME:
        m_window.close();
        break;

    default:
        break;
    }
}
