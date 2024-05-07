#include "../include/sunshine.hpp"

Sunshine::Sunshine() {
    if(!texture.loadFromFile("assets/some picture/sun.png")) {
        exit(0);
    }
    rect.top = 0;
    rect.left = 0;
    rect.width = 117;
    rect.height = 116;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    Vector2f pos(100.0, 0.0);
    sprite.setPosition(pos);
    sprite.setScale(0.5,0.5);
}


void Sunshine::update() {
    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + speed);
}

void Sunshine::render(RenderWindow* window) {
    window->draw(sprite);
}

// void Sunshine::handle_mouse_pressed() {
    
// }
