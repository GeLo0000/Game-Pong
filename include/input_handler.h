#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SFML/Window/Keyboard.hpp>

// Captures user input state for the current frame
struct InputState
{
    bool moveUp{false};
    bool moveDown{false};
    bool moveLeft{false};
    bool moveRight{false};
    bool pause{false};
    bool quit{false};
};

class InputHandler
{
public:
    // Update the input state from current keyboard status
    void update(InputState& state) const;
};

#endif // INPUT_HANDLER_H
