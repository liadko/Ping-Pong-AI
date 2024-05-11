#include "headers.hpp"
#include "simulation.hpp"
#include "neural_network.hpp"

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

    Simulation simulation;

    NeuralNetwork network(3, 1, 2);

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
                if (event.key.code == sf::Keyboard::Escape) return;
                if (event.key.code == sf::Keyboard::Space) 
                    simulation.spacePressed();
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                simulation.mouseMoved((v2f)sf::Mouse::getPosition(window), dt);
            }
            else if (event.type == sf::Event::MouseWheelScrolled)
                simulation.mouseScrolled(event.mouseWheelScroll.delta, dt);
                


        //if (frame_count % 100 == 0)
        //    cout << (1 / dt) << "\n";
        
        //simulation.handleKeys(dt);

        // Graphics
        window.clear(sf::Color::Black);

        //simulation.update(dt);
        
        //simulation.draw(window);

        network.draw(window);

        window.display(); // Render to screen

        frame_count++;
    }
}