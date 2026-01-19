#pragma once

#include <memory>

class Ball;
class Paddle;

// Supported gameplay modes
enum class ModeType { PvP, PvAI };

// Strategy interface for per-mode update logic
class GameMode {
  public:
    virtual ~GameMode() = default;
    virtual void update(float deltaTime, Ball &ball, Paddle &left,
                        Paddle &right) = 0;
};

// Player vs Player mode (both paddles controlled by users)
class PvPMode : public GameMode {
  public:
    void update(float deltaTime, Ball &ball, Paddle &left,
                Paddle &right) override;
};

// Player vs AI mode (right paddle is AI-controlled)
class PvAIMode : public GameMode {
  public:
    void update(float deltaTime, Ball &ball, Paddle &left,
                Paddle &right) override;
};

// Singleton manager to hold the current mode instance
class GameModeManager {
  public:
    static GameModeManager &instance();

    void selectMode(ModeType type);
    GameMode *currentMode();

  private:
    GameModeManager() = default;
    GameModeManager(const GameModeManager &) = delete;
    GameModeManager &operator=(const GameModeManager &) = delete;

    std::unique_ptr<GameMode> m_mode;
};
