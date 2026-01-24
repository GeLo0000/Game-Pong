#include "AudioManager.hpp"
#include <iostream>

AudioManager::AudioManager(ResourceManager &resourceMgr, EventManager &eventMgr)
    : m_resourceMgr(resourceMgr), m_eventMgr(eventMgr) {
    resourceMgr.loadSoundBuffer(kSoundPaddleHitName, kAudioPaddleHitPath);
    resourceMgr.loadSoundBuffer(kSoundWallHitName, kAudioWallHitPath);
    resourceMgr.loadSoundBuffer(kSoundGoalName, kAudioGoalPath);

    m_subscriptions.push_back(
        {EventType::PADDLE_HIT,
         m_eventMgr.subscribe(EventType::PADDLE_HIT, [this](const EventType &e) {
             playSoundEffect(kSoundPaddleHitName);
         })});
    m_subscriptions.push_back(
        {EventType::WALL_HIT, m_eventMgr.subscribe(EventType::WALL_HIT, [this](const EventType &e) {
             playSoundEffect(kSoundWallHitName);
         })});
    m_subscriptions.push_back(
        {EventType::GOAL_SCORED_LEFT,
         m_eventMgr.subscribe(EventType::GOAL_SCORED_LEFT,
                              [this](const EventType &e) { playSoundEffect(kSoundGoalName); })});
    m_subscriptions.push_back(
        {EventType::GOAL_SCORED_RIGHT,
         m_eventMgr.subscribe(EventType::GOAL_SCORED_RIGHT,
                              [this](const EventType &e) { playSoundEffect(kSoundGoalName); })});
    m_subscriptions.push_back(
        {EventType::GAME_PAUSE,
         m_eventMgr.subscribe(EventType::GAME_PAUSE,
                              [this](const EventType &e) { pauseBackgroundMusic(); })});
    m_subscriptions.push_back(
        {EventType::GAME_RESUME,
         m_eventMgr.subscribe(EventType::GAME_RESUME,
                              [this](const EventType &e) { resumeBackgroundMusic(); })});
    m_subscriptions.push_back(
        {EventType::GAME_START,
         m_eventMgr.subscribe(EventType::GAME_START, [this](const EventType &e) {
             playBackgroundMusic(kAudioBackgroundPath);
         })});

}

AudioManager::~AudioManager() {
    for (const auto &[type, id] : m_subscriptions) {
        m_eventMgr.unsubscribe(type, id);
    }
}

void AudioManager::update() {
    m_activeSounds.remove_if([](const sf::Sound &sound) {
        return sound.getStatus() == sf::SoundSource::Status::Stopped;
    });
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
    m_activeSounds.emplace_back(*buffer);
    auto &sound = m_activeSounds.back();
    sound.setVolume(volume);
    sound.play();
}
