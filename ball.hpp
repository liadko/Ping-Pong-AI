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
};