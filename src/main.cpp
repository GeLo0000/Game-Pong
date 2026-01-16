#include "window.h"

int main()
{
    // Initialize game window
    Window gameWindow(800, 600, "Pong Game");

    // Create a test shape
    sf::CircleShape testShape(50.f);
    testShape.setFillColor(sf::Color::Green);
    testShape.setPosition(375.f, 275.f);

    // Main game loop
    while (gameWindow.isOpen())
    {
        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                gameWindow.close();
            }
        }

        // Clear window
        gameWindow.clear();

        // Draw game objects
        gameWindow.draw(testShape);

        // Present rendered frame
        gameWindow.display();
    }

    return 0;
}
