#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Paddle
{
public:
    // Create paddle at specified position
    Paddle(float x, float y, float width = 20.0f, float height = 100.0f);

    // Move paddle up or down with boundary checking
    void moveUp(float speed, float topBound);
    void moveDown(float speed, float bottomBound);

    // Update paddle state (can be used for AI or smooth movement)
    void update();

    // Draw paddle to window
    void draw(sf::RenderWindow& window) const;

    // Get paddle bounds for collision detection
    sf::FloatRect getBounds() const;

    // Get paddle position
    sf::Vector2f getPosition() const;

    // Set paddle position
    void setPosition(float x, float y);

private:
    sf::RectangleShape m_shape;
    float m_speed;
};

#endif // PADDLE_H
