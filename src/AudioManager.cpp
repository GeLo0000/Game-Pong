#include "AudioManager.hpp"
#include <iostream>

AudioManager::AudioManager(ResourceManager &resourceMgr, EventManager &eventMgr)
    : m_resourceMgr(resourceMgr), m_eventMgr(eventMgr) {
    resourceMgr.loadSoundBuffer("paddle_hit", "assets/audio/paddle_hit.ogg");
    resourceMgr.loadSoundBuffer("wall_hit", "assets/audio/wall_hit.ogg");
    resourceMgr.loadSoundBuffer("goal", "assets/audio/goal.ogg");

    m_subscriptions.push_back(
        {EventType::PADDLE_HIT, m_eventMgr.subscribe(EventType::PADDLE_HIT, [this](const Event &e) {
             playSoundEffect("paddle_hit");
         })});
    m_subscriptions.push_back(
        {EventType::WALL_HIT, m_eventMgr.subscribe(EventType::WALL_HIT, [this](const Event &e) {
             playSoundEffect("wall_hit");
         })});
    m_subscriptions.push_back({EventType::GOAL_SCORED,
                               m_eventMgr.subscribe(EventType::GOAL_SCORED, [this](const Event &e) {
                                   playSoundEffect("goal");
                               })});
    m_subscriptions.push_back({EventType::GAME_PAUSED,
                               m_eventMgr.subscribe(EventType::GAME_PAUSED, [this](const Event &e) {
                                   pauseBackgroundMusic();
                               })});
    m_subscriptions.push_back(
        {EventType::GAME_RESUMED,
         m_eventMgr.subscribe(EventType::GAME_RESUMED,
                              [this](const Event &e) { resumeBackgroundMusic(); })});
}

AudioManager::~AudioManager() {
    for (const auto &[type, id] : m_subscriptions) {
        m_eventMgr.unsubscribe(type, id);
    }
}

bool AudioManager::playBackgroundMusic(const std::string &path, float volume) {
    if (path.empty()) {
        return false;
    }
    if (m_music.getStatus() == sf::SoundSource::Status::Playing) {
        return true;
    }
    if (!m_music.openFromFile(path)) {
        std::cerr << "Failed to open music: " << path << "\n";
        return false;
    }
    m_music.setLooping(true);
    m_music.setVolume(volume);
    m_music.play();
    return true;
}

void AudioManager::pauseBackgroundMusic() {
    if (m_music.getStatus() == sf::SoundSource::Status::Playing) {
        m_music.pause();
    }
}

void AudioManager::resumeBackgroundMusic() {
    if (m_music.getStatus() == sf::SoundSource::Status::Paused) {
        m_music.play();
    }
}

void AudioManager::playSoundEffect(const std::string &name, float volume) {
    const auto *buffer = m_resourceMgr.getSoundBuffer(name);
    if (!buffer) {
        return;
    }
    auto it = m_sounds.find(name);
    if (it == m_sounds.end()) {
        auto [iter, inserted] = m_sounds.try_emplace(name, *buffer);
        iter->second.setVolume(volume);
        iter->second.play();
    } else {
        it->second.setBuffer(*buffer);
        it->second.setVolume(volume);
        it->second.play();
    }
}
