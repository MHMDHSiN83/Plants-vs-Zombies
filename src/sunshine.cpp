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

bool Sunshine::handle_mouse_pressed(Vector2i mouse_position) {
    Vector2f position = sprite.getPosition();
    Vector2f sprite_size = {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height};
    if (mouse_position.x >= position.x && mouse_position.x <= position.x + sprite_size.x &&
        mouse_position.y >= position.y && mouse_position.y <= position.y + sprite_size.y) {
        return true;
    }
    return false;    
}
