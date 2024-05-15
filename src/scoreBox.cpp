#include "../include/scoreBox.hpp"

ScoreBox::ScoreBox() {
    rectangle.setSize(Vector2f(100,50));
    rectangle.setFillColor(Color::Black);
    rectangle.setPosition(200, 75);
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

    rect.top = 0;
    rect.left = 0;
    rect.width = 117;
    rect.height = 116;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setPosition(50, 30);
    if(!texture.loadFromFile("assets/some picture/sun.png")) {
        exit(0);
    }
    sprite.setScale(1.2, 1.2);
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
    window->draw(sprite);
}
