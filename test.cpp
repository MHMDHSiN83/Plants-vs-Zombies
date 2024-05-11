#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Clock Example");
    sf::Clock clock;
    bool drawRectangle = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Get the elapsed time since the last frame
        sf::Time elapsed = clock.getElapsedTime();
        cout << elapsed.asSeconds() << endl;

        // If 2 seconds have passed, set drawRectangle to true
        if (elapsed.asSeconds() >= 2 && !drawRectangle)
        {
            drawRectangle = true;
            std::cout << "2 seconds elapsed. Drawing rectangle." << std::endl;
            clock.restart();
        }

        // Clear the window
        window.clear();

        // Draw objects, UI, etc.
        if (drawRectangle)
        {
            sf::RectangleShape rectangle(sf::Vector2f(100, 100));
            rectangle.setFillColor(sf::Color::Green);
            rectangle.setPosition(100, 100);
            window.draw(rectangle);
        }

        // Display the window
        window.display();
    }

    return 0;
}
