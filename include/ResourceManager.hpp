#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

// Loads and stores reusable assets (fonts, sound buffers).
class ResourceManager {
  public:
    static ResourceManager &instance();

    bool loadFont(const std::string &name, const std::string &path);
    bool loadSoundBuffer(const std::string &name, const std::string &path);

    const sf::Font *getFont(const std::string &name) const;
    const sf::SoundBuffer *getSoundBuffer(const std::string &name) const;

  private:
    ResourceManager() = default;
    ResourceManager(const ResourceManager &) = delete;
    ResourceManager &operator=(const ResourceManager &) = delete;

    std::unordered_map<std::string, sf::Font> m_fonts;
    std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers;
};
