#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Clock Pause Example");

    sf::Clock clock; // Initialize the clock
    sf::Time pauseTime; // Time when the clock was paused
    bool paused = false; // Flag to indicate if the clock is paused

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                if (!paused)
                {
                    // Pause the clock
                    pauseTime = clock.getElapsedTime();
                    paused = true;
                    std::cout << "Clock paused.\n";
                }
                else
                {
                    // Resume the clock
                    sf::Time elapsed = clock.getElapsedTime();
                    sf::Time pauseDuration = elapsed - pauseTime;
                    clock.restart();
                    clock += pauseDuration.asMicroseconds();
                    paused = false;
                    std::cout << "Clock resumed.\n";
                }
            }
        }

        if (!paused)
        {
            // Update the clock when it's not paused
            sf::Time elapsed = clock.getElapsedTime();
            std::cout << "Elapsed time: " << elapsed.asSeconds() << " seconds.\n";
        }

        window.clear();
        window.display();
    }

    return 0;
}
