#include "Game.hpp"
#include "EventManager.hpp"
#include "GameMode.hpp"
#include "GameObjectFactory.hpp"
#include "ResourceManager.hpp"
#include "ScoreManager.hpp"
#include <string>

Game::Game()
    : m_window(sf::VideoMode({static_cast<unsigned int>(kWindowWidth),
                              static_cast<unsigned int>(kWindowHeight)}),
               "Pong Game"),
      m_currentState(GameState::MENU) {
    m_window.setFramerateLimit(kFramerateLimit);

    createGameObjects();
    initializeComponents();
    subscribeToEvents();
}

Game::~Game() = default;

void Game::createGameObjects() {
    m_leftPaddle = GameObjectFactory::createPaddle(kPaddleLeftX, kWindowHeight / 2.0f, kPaddleWidth,
                                                   kPaddleHeight, kWindowHeight);

    m_rightPaddle = GameObjectFactory::createPaddle(
        kWindowWidth - kPaddleRightXOffset - kPaddleWidth, kWindowHeight / 2.0f, kPaddleWidth,
        kPaddleHeight, kWindowHeight, true);

    m_ball = GameObjectFactory::createBall(kWindowWidth / 2.0f, kWindowHeight / 2.0f, kBallRadius,
                                           kWindowWidth, kWindowHeight);
}

void Game::initializeComponents() {
    m_audioManager =
        std::make_unique<AudioManager>(ResourceManager::instance(), EventManager::instance());
    m_uiManager = std::make_unique<UIManager>(kWindowWidth, kWindowHeight);
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
        m_audioManager->playBackgroundMusic("assets/audio/background.ogg");
        break;

    case EventType::INPUT_START_PVAI:
        GameModeManager::instance().selectMode(ModeType::PvAI);
        ScoreManager::instance().reset();
        m_ball->reset();
        m_currentState = GameState::PLAYING;
        m_audioManager->playBackgroundMusic("assets/audio/background.ogg");
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
