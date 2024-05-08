#include "headers.hpp"
#include "ball.hpp"
#include "paddle.hpp"


// return true on success? maybe?
void mainLoop(sf::RenderWindow& window);

int main()
{
    //Window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Program", sf::Style::Close, sf::ContextSettings(24, 8, 8));

    //window.setFramerateLimit(60);


    mainLoop(window);


    cout << "End Of Main Loop\n";

    return 0;
}


void mainLoop(sf::RenderWindow& window)
{

    Ball ball({ 800, HEIGHT / 2 });
    Paddle paddle(WIDTH / 2, 700);

    int frame_count = 0;
    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                return;
            else if (event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape) return;
                if (event.key.code == sf::Keyboard::Space) ball = Ball((v2f)sf::Mouse::getPosition(window));
            }
            else if (event.type == sf::Event::MouseWheelScrolled)
                paddle.rotate(event.mouseWheelScroll.delta, dt);


        //if (frame_count % 100 == 0)
        //    cout << (1 / dt) << "\n";


        // Graphics
        window.clear(sf::Color::Black);

        ball.update(paddle, dt);
        ball.draw(window);
        paddle.draw(window);

        window.display(); // Render to screen

        frame_count++;
    }
}