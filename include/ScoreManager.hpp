#pragma once

#include "EventManager.hpp"

// Singleton score tracker that listens to GOAL_SCORED events
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

    void onGoalScored(const Event &event);

    int m_leftScore;
    int m_rightScore;
    std::size_t m_subscriptionId;
};
