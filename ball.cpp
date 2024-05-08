#include "headers.hpp"
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

void Ball::update(const Paddle& paddle, float dt)
{
    // raycasting for collision check
    v2f ray_origin = paddle.getLeft(), ray_dest = paddle.getRight();
    
    // a
    v2f dir = ray_dest - ray_origin;
    float a = dot(dir, dir);


    v2f delta = velocity * dt; // where should move
    int parts = 4;
    for (int i = 0; i < parts; i++)
    {
        position += delta / (float)parts;

        // b
        v2f q2c = position - ray_origin;
        float b = -2 * dot(dir, q2c);

        // c
        float c = dot(q2c, q2c) - radius * radius;

        float discy = b * b - 4 * a * c;
         
        if (discy > 0)
        {
            // distance from ray_origin to ball hit location
            float root = sqrt(discy);
            float t1 = (-b - root) / (2.0f * a);
            float t2 = (-b + root) / (2.0f * a);
            if (!(t1 > 0 && t1 < 1) && !(t2 > 0 && t2 < 1)) continue; // not a hit

            v2f paddle_normal = { cosf(paddle.getRotation() + PI / 2), sinf(paddle.getRotation() + PI / 2) }; // normalized thanks to sin and cos!

            if (dot(velocity, paddle_normal) > 0)
                paddle_normal *= -1.0f;

            v2f reflected = velocity - 2.0f * dot(velocity, paddle_normal) * paddle_normal;

            velocity = reflected;


            //position += paddle_normal - 

            break; // hit executed
        }
    }
    
    
    
    velocity.y += g*dt;
}