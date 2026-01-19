#include "EventManager.hpp"

#include <algorithm>

EventManager &EventManager::instance() {
    static EventManager inst;
    return inst;
}

std::size_t EventManager::subscribe(EventType type, Callback cb) {
    const std::size_t id = m_nextId++;
    m_listeners[type].push_back({id, std::move(cb)});
    return id;
}

void EventManager::unsubscribe(EventType type, std::size_t id) {
    auto &vec = m_listeners[type];
    vec.erase(std::remove_if(vec.begin(), vec.end(),
                             [id](const auto &p) { return p.first == id; }),
              vec.end());
}

void EventManager::emit(const Event &event) {
    auto it = m_listeners.find(event.type);
    if (it == m_listeners.end()) {
        return;
    }

    for (const auto &[_, cb] : it->second) {
        if (cb) {
            cb(event);
        }
    }
}
