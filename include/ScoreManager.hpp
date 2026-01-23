#pragma once

#include "EventManager.hpp"

class ScoreManager {
  public:
    static ScoreManager &instance();

    int getLeftScore() const;
    int getRightScore() const;

    void addLeftScore();
    void addRightScore();
    void reset();

  private:
    ScoreManager();
    ScoreManager(const ScoreManager &) = delete;
    ScoreManager &operator=(const ScoreManager &) = delete;

    int m_leftScore;
    int m_rightScore;
    std::size_t m_subscriptionIdLeft;
    std::size_t m_subscriptionIdRight;
};
