#pragma once

#include <memory>

class Ball;
class Paddle;

enum class ModeType { PvP, PvAI };

class GameMode {
  public:
    virtual ~GameMode() = default;
    virtual void update(float deltaTime, Ball &ball, Paddle &left, Paddle &right) = 0;
};

class PvPMode : public GameMode {
  public:
    void update(float deltaTime, Ball &ball, Paddle &left, Paddle &right) override;
};

class PvAIMode : public GameMode {
  public:
    void update(float deltaTime, Ball &ball, Paddle &left, Paddle &right) override;
};

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
