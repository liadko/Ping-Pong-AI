#include "simulation.hpp"
#include "utils.hpp"

Simulation::Simulation() : paddle(WIDTH / 2, 700), ball({ WIDTH/2, 200 })
{
    srand(time(NULL));


}

bool Simulation::handleHit()
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

    //if (dot(ball.getVelocity(), paddle.getNormal()) > 0)
    //    paddle.flipNormal();

    if (paddle.normal_flipped)
        cout << "Up\n";
    else
        cout << "Down\n";

    v2f paddle_normal = paddle.getNormal();

    v2f reflected = ball.getVelocity() - 2.0f * dot(ball.getVelocity(), paddle_normal) * paddle_normal;
    
    
    v2f hit_direction = paddle.velocity;
    hit_direction.x *= 0.5f;
    hit_direction.x += rand() / (float)RAND_MAX * 10;


    float reflection_weight = 0.9f;
    float hit_direction_weight = 1.0f;
    
    // small dot product, the hit is at an angle
    /*if (abs(dot(hit_direction, paddle_normal)) < 1)
    {
        cout << "sideways hit\n";
        hit_direction_weight *= (0.3f +);
    }*/

    v2f new_velocity = reflected * reflection_weight + hit_direction * hit_direction_weight;
    float ball_speed = len(new_velocity);
    if (ball_speed > 1.5f * paddle.speed)
        new_velocity = new_velocity / ball_speed * 1.5f * paddle.speed; // set speed to paddle speed

    ball.setVelocity(new_velocity);

    // adjust for ball immersion (get ball outside of the paddle)

    float ball_slice = abs(t2 - t1) / 2.0f;
    float penetration_amount = ball.getRadius() - sqrt(ball.getRadius() * ball.getRadius() - ball_slice * ball_slice);
    ball.setPosition(ball.getPosition() + paddle_normal * 2.0f *  (penetration_amount + 1.0f));
    

    return true; // hit executed

}


void Simulation::update(float dt)
{

    updateBall(dt);
    updatePaddle(dt);

    //cout << "Ball Speed: " << len(ball.velocity) << "\n";
}

void Simulation::updateBall(float dt)
{
    int parts = 5;
    for (int i = 0; i < parts; i++)
    {
        handleHit();
        
        
        ball.position += ball.velocity * dt / (float)parts;

    }



    ball.velocity.y += g * dt;
}
void Simulation::updatePaddle(float dt)
{
    if (paddle.velocity.x == 0 && paddle.velocity.y == 0)
        return;
        
    int parts = 5;
    v2f delta = paddle.velocity * dt / (float)parts ;
    for (int i = 0; i < parts; i++)
    {
        if (handleHit())
            break;

        paddle.position += delta;
    }
}

void Simulation::draw(sf::RenderWindow& window)
{
    paddle.draw(window);
    ball.draw(window);
}


#define KEY_PRESSED(key) sf::Keyboard::isKeyPressed(sf::Keyboard::Key::key)
void Simulation::handleKeys(float dt)
{

    // move
    v2f movement(0, 0);
    if (KEY_PRESSED(W))
        movement.y += -1;
    if (KEY_PRESSED(A))
        movement.x += -1;
    if (KEY_PRESSED(S))
        movement.y += +1;
    if (KEY_PRESSED(D))
        movement.x += +1;

    paddle.velocity = movement * paddle.speed;

}

void Simulation::spacePressed()
{
    ball = Ball({WIDTH/2, 200});
}

void Simulation::mouseMoved(const v2f& mouse_position, float dt)
{

    //movePaddleTo(mouse_position, dt);

}

void Simulation::movePaddle(const v2f& move, float dt)
{
    
}

void Simulation::mouseScrolled(int delta, float dt)
{
    paddle.rotate(-delta, dt);
}

