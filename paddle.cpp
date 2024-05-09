#include "headers.hpp"
#include "paddle.hpp"
#include "utils.hpp"

Paddle::Paddle(float x, float y) : position(x, y)
{
    rect_shape.setSize(size);
    rect_shape.setFillColor(sf::Color::White);
    rect_shape.setOrigin(size.x/2, size.y/2);

    //normal_direction = { cosf(getRotation() + PI / 2), sinf(getRotation() + PI / 2) };

    updateNormal();
}

void Paddle::draw(sf::RenderWindow& window)
{
    /*sf::Vertex line[] = 
        {sf::Vertex(getLeft(), sf::Color::Blue),
        sf::Vertex(getRight(), sf::Color::Blue)};
    window.draw(line, 2, sf::Lines);*/

    rect_shape.setPosition(position);
    rect_shape.setRotation(rotation * TO_DEGREES);
    window.draw(rect_shape);

    // normal
    
    
    drawVector(position, normal_direction, sf::Color::Blue, window);
    
    
    drawVector(position, velocity, sf::Color::Red, window);



}

void Paddle::rotate(float scroll, float dt)
{
    rotation += scroll * rotation_speed * dt;

    updateNormal();
}


void Paddle::setPosition(const v2f& new_pos)
{
    position = new_pos;
}

void Paddle::flipNormal()
{
    normal_flipped ^= 1; 

    updateNormal();
}

void Paddle::updateNormal()
{
    // normalized thanks to sin and cos!
    normal_direction = { cosf(getRotation() + PI / 2), sinf(getRotation() + PI / 2) };

    if (normal_flipped)
        normal_direction *= -1.0f;
}