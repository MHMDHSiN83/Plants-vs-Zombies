#include <SFML/Graphics.hpp>

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Centered Text in Rectangle");

    // Create a RectangleShape
    sf::RectangleShape rectangle(sf::Vector2f(200, 100));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(300, 200);

    // Create a font
    sf::Font font;
    if (!font.loadFromFile("assets/ARIAL.TTF")) {
        return EXIT_FAILURE;
    }

    // Create a Text
    sf::Text text("Centered Text", font, 24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    // Calculate the center position of the text
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                   textBounds.top + textBounds.height / 2.0f);
    text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2.0f,
                     rectangle.getPosition().y + rectangle.getSize().y / 2.0f);

    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear();

        // Draw the rectangle and text
        window.draw(rectangle);
        window.draw(text);

        // Display the window
        window.display();
    }

    return EXIT_SUCCESS;
}
