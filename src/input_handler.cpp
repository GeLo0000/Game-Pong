#include "input_handler.h"

void InputHandler::update(InputState& state) const
{
    state.moveUp = sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    state.moveDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    state.moveLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    state.moveRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    state.pause = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    state.quit = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
}
