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
    


public:
    Simulation();
    

    void mouseMoved(const v2i& mousePosition);
    void spacePressed(const v2i& mousePosition);
    void mouseScrolled(int delta, float dt);
    void update(float dt);

    void draw(sf::RenderWindow& window);

    //static methods
    static bool handleHit(Ball& ball, Paddle& paddle);
};