#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

enum class EventType {
    PADDLE_HIT,
    WALL_HIT,
    GOAL_SCORED,
    GAME_PAUSED,
    GAME_RESUMED,

    INPUT_START_PVP,
    INPUT_START_PVAI,
    INPUT_PAUSE,
    INPUT_RESUME,
    INPUT_RESTART,
    INPUT_BACK_TO_MENU,
    INPUT_CLOSE_GAME
};

struct Event {
    EventType type;
    const char *info;
};

class EventManager {
  public:
    using Callback = std::function<void(const Event &)>;

    static EventManager &instance();

    std::size_t subscribe(EventType type, Callback cb);

    void unsubscribe(EventType type, std::size_t id);

    void emit(const Event &event);

  private:
    EventManager() = default;
    EventManager(const EventManager &) = delete;
    EventManager &operator=(const EventManager &) = delete;

    std::unordered_map<EventType, std::vector<std::pair<std::size_t, Callback>>> m_listeners;
    std::size_t m_nextId{1};
};
