#include "ScoreManager.hpp"
#include <cstring>

ScoreManager &ScoreManager::instance() {
    static ScoreManager inst;
    return inst;
}

ScoreManager::ScoreManager() : m_leftScore(0), m_rightScore(0) {
    // Subscribe to GOAL_SCORED events
    m_subscriptionId = EventManager::instance().subscribe(
        EventType::GOAL_SCORED, [this](const Event &e) { onGoalScored(e); });
}

int ScoreManager::getLeftScore() const { return m_leftScore; }

int ScoreManager::getRightScore() const { return m_rightScore; }

void ScoreManager::addLeftScore() { ++m_leftScore; }

void ScoreManager::addRightScore() { ++m_rightScore; }

void ScoreManager::reset() {
    m_leftScore = 0;
    m_rightScore = 0;
}

// Determine which side scored based on event info
void ScoreManager::onGoalScored(const Event &event) {
    if (std::strcmp(event.info, "right wall") == 0) {
        addLeftScore();
    } else if (std::strcmp(event.info, "left wall") == 0) {
        addRightScore();
    }
}
