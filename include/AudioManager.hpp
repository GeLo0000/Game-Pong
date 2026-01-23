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

  private:
    ResourceManager &m_resourceMgr;
    EventManager &m_eventMgr;

    sf::Music m_music;
    std::unordered_map<std::string, sf::Sound> m_sounds;
    std::vector<std::pair<EventType, std::size_t>> m_subscriptions;
};
