#pragma once

#include "EventManager.hpp"

// Observer interface for event handling
class IEventListener {
  public:
    virtual ~IEventListener() = default;
    virtual void onEvent(const Event &event) = 0;
};
