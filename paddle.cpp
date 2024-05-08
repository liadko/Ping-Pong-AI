#include "headers.hpp"
#include "paddle.hpp"
#include "utils.hpp"

Paddle::Paddle(float x, float y) : position(x, y)
{
    rect_shape.setSize(size);
    rect_shape.setFillColor(sf::Color::White);
    rect_shape.setOrigin(size.x/2, size.y/2);
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
    v2f normal = { cosf(getRotation() + PI / 2), sinf(getRotation() + PI / 2) };
    
    drawVector(position, normal, window);


    //// raycast
    //v2f ray_origin = getLeft(), ray_dest = getRight();

    //// a
    //v2f dir = ray_dest - ray_origin;
    //drawVector(ray_origin, dir, window);
}

void Paddle::rotate(float scroll, float dt)
{
    rotation += scroll * rotation_speed * dt;
    normal_direction = { cosf(getRotation() + PI / 2), sinf(getRotation() + PI / 2) };
    if (normal_flipped)
        normal_direction *= -1.0f;
}