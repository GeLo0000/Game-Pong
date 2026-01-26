#pragma once

#include "EventManager.hpp"

class ScoreManager {
  public:
    ScoreManager(EventManager &eventMgr);

    int getLeftScore() const;
    int getRightScore() const;

    void addLeftScore();
    void addRightScore();
    void reset();

  private:
    EventManager &m_eventMgr;
    int m_leftScore;
    int m_rightScore;
    std::size_t m_subscriptionIdLeft;
    std::size_t m_subscriptionIdRight;
};
