#include "window.h"

Window::Window(unsigned int width, unsigned int height, const std::string& title)
    : m_width(width), m_height(height)
{
    m_window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(width, height),
        title
    );
    m_window->setFramerateLimit(60);  // 60 FPS
}

bool Window::isOpen() const
{
    return m_window && m_window->isOpen();
}

void Window::close()
{
    if (m_window)
    {
        m_window->close();
    }
}

bool Window::pollEvent(sf::Event& event)
{
    if (!m_window)
        return false;
    
    return m_window->pollEvent(event);
}

void Window::clear(const sf::Color& color)
{
    if (m_window)
    {
        m_window->clear(color);
    }
}

void Window::draw(const sf::Drawable& drawable)
{
    if (m_window)
    {
        m_window->draw(drawable);
    }
}

void Window::display()
{
    if (m_window)
    {
        m_window->display();
    }
}

unsigned int Window::getWidth() const
{
    return m_width;
}

unsigned int Window::getHeight() const
{
    return m_height;
}

sf::RenderWindow* Window::getRenderWindow()
{
    return m_window.get();
}
