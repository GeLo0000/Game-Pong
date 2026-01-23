#include "ScoreManager.hpp"
#include <cstring>

ScoreManager &ScoreManager::instance() {
    static ScoreManager inst;
    return inst;
}

ScoreManager::ScoreManager() : m_leftScore(0), m_rightScore(0) {
    m_subscriptionIdLeft = EventManager::instance().subscribe(
        EventType::GOAL_SCORED_LEFT, [this](const EventType &e) { addLeftScore(); });
    m_subscriptionIdRight = EventManager::instance().subscribe(
        EventType::GOAL_SCORED_RIGHT, [this](const EventType &e) { addRightScore(); });
}

int ScoreManager::getLeftScore() const { return m_leftScore; }

int ScoreManager::getRightScore() const { return m_rightScore; }

void ScoreManager::addLeftScore() { ++m_leftScore; }

void ScoreManager::addRightScore() { ++m_rightScore; }

void ScoreManager::reset() {
    m_leftScore = 0;
    m_rightScore = 0;
}
