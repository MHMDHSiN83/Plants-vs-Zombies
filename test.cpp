#include <SFML/Graphics.hpp>
#include <cmath> // Include cmath for sqrt()

bool areSpritesIntersecting(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
    // Get the bounds of each sprite
    sf::FloatRect bounds1 = sprite1.getGlobalBounds();
    sf::FloatRect bounds2 = sprite2.getGlobalBounds();

    // Calculate the center of each sprite
    sf::Vector2f center1(bounds1.left + bounds1.width / 2, bounds1.top + bounds1.height / 2);
    sf::Vector2f center2(bounds2.left + bounds2.width / 2, bounds2.top + bounds2.height / 2);

    // Calculate the distance between the centers of the sprites
    float distance = std::sqrt((center1.x - center2.x) * (center1.x - center2.x) +
                               (center1.y - center2.y) * (center1.y - center2.y));

    // Calculate the sum of the half-widths of the sprites
    float sumOfHalfWidths = (bounds1.width / 2) + (bounds2.width / 2);
    // Calculate the sum of the half-heights of the sprites
    float sumOfHalfHeights = (bounds1.height / 2) + (bounds2.height / 2);

    // Check if the distance between the centers is less than the sum of half-widths and half-heights
    return distance < sumOfHalfWidths && distance < sumOfHalfHeights;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Intersecting Sprites");

    // Create two sprites
    sf::Texture texture1;
    texture1.loadFromFile("assets/pea.png");
    sf::Sprite sprite1(texture1);
    sprite1.setPosition(100, 100);

    sf::Texture texture2;
    texture2.loadFromFile("assets/zom/1.png");
    sf::Sprite sprite2(texture2);
    sprite2.setPosition(200, 200);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Check if the sprites intersect
        if (areSpritesIntersecting(sprite1, sprite2)) {
            // Handle collision here
            // For example: change color, destroy sprites, etc.
            sprite1.setColor(sf::Color::Red);
            sprite2.setColor(sf::Color::Red);
        } else {
            // If not intersecting, reset the colors
            sprite1.setColor(sf::Color::White);
            sprite2.setColor(sf::Color::White);
        }

        window.clear();
        window.draw(sprite1);
        window.draw(sprite2);
        window.display();
    }

    return 0;
}
