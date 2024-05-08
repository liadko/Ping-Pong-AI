#include "headers.hpp"
#include "simulation.hpp"
#include "ball.hpp"
#include "paddle.hpp"
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

    drawVector(position, velocity, window);
}

void Ball::update(Paddle& paddle, float dt)
{
    


    v2f delta = velocity * dt; // where should move
    int parts = 4;
    for (int i = 0; i < parts; i++)
    {
        position += delta / (float)parts;

        if (Simulation::handleHit(*this, paddle))
            break;
    }
    
    
    
    velocity.y += g*dt;
}