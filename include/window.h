#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <memory>

// Wrapper class for SFML RenderWindow
class Window
{
public:
    // Initialize window with width, height and title
    Window(unsigned int width, unsigned int height, const std::string& title);

    // Destructor
    ~Window() = default;

    // Check if window is open
    bool isOpen() const;

    // Close the window
    void close();

    // Poll events from window
    bool pollEvent(sf::Event& event);

    // Clear window with specified color (default is black)
    void clear(const sf::Color& color = sf::Color::Black);

    // Draw drawable object to window
    void draw(const sf::Drawable& drawable);

    // Display the rendered frame
    void display();

    // Get window width in pixels
    unsigned int getWidth() const;

    // Get window height in pixels
    unsigned int getHeight() const;

    // Get pointer to internal SFML RenderWindow for advanced usage
    sf::RenderWindow* getRenderWindow();

private:
    std::unique_ptr<sf::RenderWindow> m_window;
    unsigned int m_width;
    unsigned int m_height;
};

#endif // WINDOW_H
