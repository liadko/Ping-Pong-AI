#pragma once
#include "headers.hpp"
#include "ball.hpp"
#include "paddle.hpp"

class Simulation
{
private:
    // game objects
    Paddle paddle;
    Ball ball;
    
    const float g = 2000;
    const float friction = 0.1f;

public:
    Simulation();
    
    void updateBall(float dt);
    void updatePaddle(float dt);
    bool handleHit();

    void handleKeys(float dt);
    void movePaddle(const v2f& move, float dt);

    void mouseMoved(const v2f& mouse_position, float dt);
    void spacePressed();
    void mouseScrolled(int delta, float dt);
    void update(float dt);

    void draw(sf::RenderWindow& window);

};