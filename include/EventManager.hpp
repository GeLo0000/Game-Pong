#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

// Types of game events
enum class EventType {
    PADDLE_HIT,
    WALL_HIT,
    GOAL_SCORED,
    GAME_PAUSED,
    GAME_RESUMED
};

// Event data container
struct Event {
    EventType type;
    const char *info; // Optional short context string
};

// Singleton EventManager to broadcast events to subscribers
class EventManager {
  public:
    using Callback = std::function<void(const Event &)>;

    static EventManager &instance();

    // Subscribe to event type; returns subscription id
    std::size_t subscribe(EventType type, Callback cb);

    // Unsubscribe by id
    void unsubscribe(EventType type, std::size_t id);

    // Emit event to all subscribers
    void emit(const Event &event);

  private:
    EventManager() = default;
    EventManager(const EventManager &) = delete;
    EventManager &operator=(const EventManager &) = delete;

    std::unordered_map<EventType, std::vector<std::pair<std::size_t, Callback>>>
        m_listeners;
    std::size_t m_nextId{1};
};
