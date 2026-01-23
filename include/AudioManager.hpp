#pragma once

#include "EventManager.hpp"
#include "ResourceManager.hpp"
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <vector>

class AudioManager {
  public:
    AudioManager(ResourceManager &resourceMgr, EventManager &eventMgr);
    ~AudioManager();
    bool playBackgroundMusic(const std::string &path, float volume = 20.0f);
    void pauseBackgroundMusic();
    void resumeBackgroundMusic();

    void playSoundEffect(const std::string &name, float volume = 65.0f);

    static constexpr auto kSoundPaddleHitName = "paddleHitSound";
    static constexpr auto kSoundWallHitName = "wallHitSound";
    static constexpr auto kSoundGoalName = "goalSound";

    static constexpr auto kAudioPaddleHitPath = "assets/audio/paddle_hit.ogg";
    static constexpr auto kAudioWallHitPath = "assets/audio/wall_hit.ogg";
    static constexpr auto kAudioGoalPath = "assets/audio/goal.ogg";
    static constexpr auto kAudioBackgroundPath = "assets/audio/background.ogg";

  private:
    ResourceManager &m_resourceMgr;
    EventManager &m_eventMgr;

    sf::Music m_music;
    std::unordered_map<std::string, sf::Sound> m_sounds;
    std::vector<std::pair<EventType, std::size_t>> m_subscriptions;
};
