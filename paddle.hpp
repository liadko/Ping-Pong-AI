#pragma once
#include "headers.hpp"

class Paddle
{
private:
    // game state
    v2f position;
    v2f size = { 160, 8 };
    
    float rotation = 0, rotation_speed = 200;

    // sprites
    sf::RectangleShape rect_shape;

    bool normal_flipped = false;
    v2f normal_direction;

public:
    Paddle(float x, float y);

    void flipNormal();
    void rotate(float scroll, float dt);

    // getters
    v2f getPosition() const { return position; };
    v2f getSize() const { return size; };
    float getRotation() const { return rotation; };
    v2f getNormal() const { return normal_direction; };
    v2f getRight() const { return { position.x + size.x / 2 * cosf(rotation), position.y + size.x / 2 * sinf(rotation) }; };
    v2f getLeft() const { return { position.x - size.x / 2 * cosf(rotation), position.y - size.x / 2 * sinf(rotation) }; };



    void draw(sf::RenderWindow& window);
};