#include "ScoreManager.hpp"

ScoreManager::ScoreManager(EventManager &eventMgr)
    : m_leftScore(0), m_rightScore(0), m_eventMgr(eventMgr) {
    m_subscriptionIdLeft = m_eventMgr.subscribe(EventType::GOAL_SCORED_LEFT,
                                                [this](const EventType &e) { addRightScore(); });
    m_subscriptionIdRight = m_eventMgr.subscribe(EventType::GOAL_SCORED_RIGHT,
                                                 [this](const EventType &e) { addLeftScore(); });
}

ScoreManager::~ScoreManager() {
    m_eventMgr.unsubscribe(EventType::GOAL_SCORED_LEFT, m_subscriptionIdLeft);
    m_eventMgr.unsubscribe(EventType::GOAL_SCORED_RIGHT, m_subscriptionIdRight);
}

int ScoreManager::getLeftScore() const { return m_leftScore; }

int ScoreManager::getRightScore() const { return m_rightScore; }

void ScoreManager::addLeftScore() { ++m_leftScore; }

void ScoreManager::addRightScore() { ++m_rightScore; }

void ScoreManager::reset() {
    m_leftScore = 0;
    m_rightScore = 0;
}
