#include "headers.hpp"
#include "simulation.hpp"
#include "neural_network.hpp"
#include "population.hpp"
#include "utils.hpp"

// return true on success? maybe?
void mainLoop(sf::RenderWindow& window);

int main()
{
    srand(time(NULL));

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


    Population population;

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
                {
                    //cout << "Network Output: ";
                    //printVec(network.runNetwork({ 1, 0 }));

                    population.progressGeneration();


                    cout << population.getNet().runNetwork({ 0, 0 })[0] << " " << population.getNet().runNetwork({ 1, 0 })[0] << "\n";
                    cout << population.getNet().runNetwork({ 0, 1 })[0] << " " << population.getNet().runNetwork({ 1, 1 })[0] << "\n\n";
                }
                    //simulation.spacePressed();
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

        population.getNet().draw(window);




        window.display(); // Render to screen

        frame_count++;
    }
}