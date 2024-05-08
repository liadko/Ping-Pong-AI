#pragma once
#include "headers.hpp"
#include "paddle.hpp"

class Ball
{
private:
    // game state
    v2f position, velocity;
    float radius = 15;//5;

    // sprites
    sf::CircleShape circle_shape;


public:
    Ball(v2f pos);

    void draw(sf::RenderWindow& window);

    void update(Paddle& paddle, float dt);

    v2f getPosition() const { return position; };
    void setPosition(const v2f& pos) { position = pos; };
    float getRadius() const { return radius; };
    v2f getVelocity() const { return velocity; };
    void setVelocity(const v2f& vel) { velocity = vel; };
};