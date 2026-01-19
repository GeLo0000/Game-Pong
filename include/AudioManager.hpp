#pragma once

#include "EventManager.hpp"
#include "ResourceManager.hpp"
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <vector>

// Manages music and sound effects, reacting to emitted events.
class AudioManager {
  public:
    static AudioManager &instance();

    bool playBackgroundMusic(const std::string &path, float volume = 5.0f);
    void pauseBackgroundMusic();
    void resumeBackgroundMusic();

    void playSoundEffect(const std::string &name, float volume = 20.0f);

  private:
    AudioManager();
    ~AudioManager();

    AudioManager(const AudioManager &) = delete;
    AudioManager &operator=(const AudioManager &) = delete;

    void onEvent(const Event &event);
    void ensureSound(const std::string &name, const std::string &path);

    sf::Music m_music;
    std::unordered_map<std::string, sf::Sound> m_sounds;
    std::vector<std::pair<EventType, std::size_t>> m_subscriptions;
};
