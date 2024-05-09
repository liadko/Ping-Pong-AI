#include "headers.hpp"
#include "ball.hpp"
#include "utils.hpp"

Ball::Ball(v2f pos) : position(pos), velocity(0, 0)
{
    circle_shape.setRadius(radius);
    circle_shape.setFillColor(sf::Color::White);
    circle_shape.setOrigin(radius, radius);
}

void Ball::draw(sf::RenderWindow& window)
{
    
    circle_shape.setPosition(position);
    window.draw(circle_shape);

    drawVector(position, velocity, sf::Color::Red, window);
}
