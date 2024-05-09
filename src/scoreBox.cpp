#include "../include/scoreBox.hpp"

ScoreBox::ScoreBox() {
    rectangle.setSize(Vector2f(100,50));
    rectangle.setFillColor(Color::Black);
    rectangle.setPosition(150, 50);
    if (!font.loadFromFile("assets/ARIAL.TTF")) {
        exit(0);
    }
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(Color::White);
    text.setStyle(Text::Bold);
    FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                   textBounds.top + textBounds.height / 2.0f);
    text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2.0f,
                     rectangle.getPosition().y + rectangle.getSize().y / 2.0f);
}

void ScoreBox::render(RenderWindow* window, int sun) {
    window->draw(rectangle);
    FloatRect textBounds = text.getLocalBounds();
    text.setString(to_string(sun));
    text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                   textBounds.top + textBounds.height / 2.0f);
    text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2.0f,
                     rectangle.getPosition().y + rectangle.getSize().y / 2.0f);
    window->draw(text);
}
