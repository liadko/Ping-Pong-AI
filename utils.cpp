#include "utils.hpp"

float len(const v2f& vec)
{
    if (vec.x == 0 && vec.y == 0) return 0;
    return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

v2f normalized(const v2f& vec)
{
    return vec / len(vec);
}

float dot(const v2f& v1, const v2f& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

void drawVector(const v2f& origin, const v2f& direction, sf::Color color, sf::RenderWindow& window)
{
    if (direction.x == 0 && direction.y == 0) return;

    sf::Vertex line[] =
    { sf::Vertex(origin, sf::Color::White),
    sf::Vertex(origin + normalized(direction) * 30.0f, color)};


    window.draw(line, 2, sf::Lines);
}