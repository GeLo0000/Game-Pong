#pragma once

#include "EventManager.hpp"

class ScoreManager {
  public:
    ScoreManager(EventManager &eventMgr);
    ~ScoreManager();

    int getLeftScore() const;
    int getRightScore() const;

    void addLeftScore();
    void addRightScore();
    void reset();

  private:
    EventManager &m_eventMgr;
    int m_leftScore = 0;
    int m_rightScore = 0;
    std::size_t m_subscriptionIdLeft = 0;
    std::size_t m_subscriptionIdRight = 0;
};
