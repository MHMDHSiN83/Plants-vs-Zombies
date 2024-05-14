#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Text Size");

    // Create a font
    sf::Font font;
    if (!font.loadFromFile("assets/ARIAL.TTF")) // Load a font
    {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }

    // Create a text
    sf::Text text("Hello, SFML!", font, 24);

    // Get the size of the text
    sf::FloatRect textBounds = text.getGlobalBounds();

    // Display the size of the text
    std::cout << "Text size: " << textBounds.width << " x " << textBounds.height << std::endl;

    // Main loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear();

        // Draw the text
        window.draw(text);

        // Display the window
        window.display();
    }

    return 0;
}
