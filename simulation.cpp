#include "headers.hpp"
#include "simulation.hpp"
#include "utils.hpp"

Simulation::Simulation() : paddle(WIDTH / 2, 700), ball({ 800, HEIGHT / 2 })
{


}

bool Simulation::handleHit(Ball& ball, Paddle& paddle)
{
    // raycasting for collision check
    v2f ray_origin = paddle.getLeft(), ray_dest = paddle.getRight();

    // a
    v2f dir = ray_dest - ray_origin;
    float a = dot(dir, dir);

    // b
    v2f q2c = ball.getPosition() - ray_origin;
    float b = -2 * dot(dir, q2c);

    // c
    float c = dot(q2c, q2c) - ball.getRadius() * ball.getRadius();

    float discy = b * b - 4 * a * c;

    if (discy <= 0) // no hit
        return false;

    // distance from ray_origin to ball hit location
    float root = sqrt(discy);
    float t1 = (-b - root) / (2.0f * a);
    float t2 = (-b + root) / (2.0f * a);

    if (!(t1 > 0 && t1 < 1) && !(t2 > 0 && t2 < 1)) return false; // not a hit

    if (dot(ball.getVelocity(), paddle.getNormal()) > 0)
        paddle.flipNormal();

    v2f paddle_normal = paddle.getNormal();

    v2f reflected = ball.getVelocity() - 2.0f * dot(ball.getVelocity(), paddle_normal) * paddle_normal;

    ball.setVelocity(reflected);

    // adjust for ball immersion
    cout << "Ball Slice: " << t2 - t1 << "\n";

    float ball_slice = abs(t2 - t1) / 2.0f;
    float penteration_amount = ball.getRadius() - sqrt(ball.getRadius() * ball.getRadius() - ball_slice * ball_slice);
    ball.setPosition(ball.getPosition() + paddle_normal * penteration_amount); 

    return true; // hit executed

}

void Simulation::update(float dt)
{
    ball.update(paddle, dt);
}

void Simulation::draw(sf::RenderWindow& window)
{
    paddle.draw(window);
    ball.draw(window);
}

void Simulation::spacePressed(const v2i& mousePosition)
{
    ball = Ball((v2f)mousePosition);
}

void Simulation::mouseScrolled(int delta, float dt)
{
    paddle.rotate(-delta, dt);
}

