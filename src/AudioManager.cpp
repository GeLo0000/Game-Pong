#include "AudioManager.hpp"

#include <iostream>

AudioManager &AudioManager::instance() {
    static AudioManager inst;
    return inst;
}

AudioManager::AudioManager() {
    // Preload all sound buffers to avoid first-play delay
    auto &rm = ResourceManager::instance();
    rm.loadSoundBuffer("paddle_hit", "assets/audio/paddle_hit.ogg");
    rm.loadSoundBuffer("wall_hit", "assets/audio/wall_hit.ogg");
    rm.loadSoundBuffer("goal", "assets/audio/goal.ogg");

    // Subscribe to events we need
    auto &em = EventManager::instance();
    m_subscriptions.push_back(
        {EventType::PADDLE_HIT,
         em.subscribe(EventType::PADDLE_HIT,
                      [this](const Event &e) { onEvent(e); })});
    m_subscriptions.push_back(
        {EventType::WALL_HIT,
         em.subscribe(EventType::WALL_HIT,
                      [this](const Event &e) { onEvent(e); })});
    m_subscriptions.push_back(
        {EventType::GOAL_SCORED,
         em.subscribe(EventType::GOAL_SCORED,
                      [this](const Event &e) { onEvent(e); })});
    m_subscriptions.push_back(
        {EventType::GAME_PAUSED,
         em.subscribe(EventType::GAME_PAUSED,
                      [this](const Event &e) { onEvent(e); })});
    m_subscriptions.push_back(
        {EventType::GAME_RESUMED,
         em.subscribe(EventType::GAME_RESUMED,
                      [this](const Event &e) { onEvent(e); })});
}

AudioManager::~AudioManager() {
    auto &em = EventManager::instance();
    for (const auto &[type, id] : m_subscriptions) {
        em.unsubscribe(type, id);
    }
}

bool AudioManager::playBackgroundMusic(const std::string &path, float volume) {
    if (path.empty()) {
        return false;
    }
    // Don't restart if already playing the same file
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
    const auto *buffer = ResourceManager::instance().getSoundBuffer(name);
    if (!buffer) {
        return; // Not loaded; fail silently to avoid crashes
    }
    auto it = m_sounds.find(name);
    if (it == m_sounds.end()) {
        // Create sound in map first, then play
        auto [iter, inserted] = m_sounds.try_emplace(name, *buffer);
        iter->second.setVolume(volume);
        iter->second.play();
    } else {
        it->second.setBuffer(*buffer);
        it->second.setVolume(volume);
        it->second.play();
    }
}

void AudioManager::ensureSound(const std::string &name,
                               const std::string &path) {
    if (ResourceManager::instance().getSoundBuffer(name)) {
        return;
    }
    ResourceManager::instance().loadSoundBuffer(name, path);
}

void AudioManager::onEvent(const Event &event) {
    switch (event.type) {
    case EventType::PADDLE_HIT:
        playSoundEffect("paddle_hit");
        break;
    case EventType::WALL_HIT:
        playSoundEffect("wall_hit");
        break;
    case EventType::GOAL_SCORED:
        playSoundEffect("goal");
        break;
    case EventType::GAME_PAUSED:
        pauseBackgroundMusic();
        break;
    case EventType::GAME_RESUMED:
        resumeBackgroundMusic();
        break;
    }
}
