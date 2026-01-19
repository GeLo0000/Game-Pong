#include "ResourceManager.hpp"

#include <iostream>

ResourceManager &ResourceManager::instance() {
    static ResourceManager inst;
    return inst;
}

bool ResourceManager::loadFont(const std::string &name,
                               const std::string &path) {
    sf::Font font;
    if (!font.openFromFile(path)) {
        std::cerr << "Failed to load font: " << path << "\n";
        return false;
    }
    m_fonts[name] = std::move(font);
    return true;
}

bool ResourceManager::loadSoundBuffer(const std::string &name,
                                      const std::string &path) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(path)) {
        std::cerr << "Failed to load sound: " << path << "\n";
        return false;
    }
    m_soundBuffers[name] = std::move(buffer);
    return true;
}

const sf::Font *ResourceManager::getFont(const std::string &name) const {
    auto it = m_fonts.find(name);
    return it != m_fonts.end() ? &it->second : nullptr;
}

const sf::SoundBuffer *
ResourceManager::getSoundBuffer(const std::string &name) const {
    auto it = m_soundBuffers.find(name);
    return it != m_soundBuffers.end() ? &it->second : nullptr;
}
