#pragma once
#include "headers.hpp"

class Paddle
{
    friend class Simulation;

private:
    // game state
    v2f position;
    v2f size = { 160, 8 };
    
    float speed = 1000.0f;
    v2f velocity;
    v2f last_pos; // for velocity calculation

    float rotation = 0, rotation_speed = 300;

    // sprites
    sf::RectangleShape rect_shape;

    bool normal_flipped = true;
    v2f normal_direction;

public:
    Paddle(float x, float y);

    //void update(Ball& ball, float dt);

    void flipNormal();
    void rotate(float scroll, float dt);

    // getters
    v2f getPosition() const { return position; }
    void setPosition(const v2f& pos);
    
    void setVelocity(const v2f& vel) { velocity = vel; }

    v2f getSize() const { return size; }
    float getRotation() const { return rotation; }


    v2f getRight() const { return { position.x + size.x / 2 * cosf(rotation), position.y + size.x / 2 * sinf(rotation) }; }
    v2f getLeft() const { return { position.x - size.x / 2 * cosf(rotation), position.y - size.x / 2 * sinf(rotation) }; }

    v2f getNormal() const { return normal_direction; }
    void updateNormal();

    void draw(sf::RenderWindow& window);
};