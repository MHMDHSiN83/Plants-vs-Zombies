
#include "../include/sunshine.hpp"

Sunshine::Sunshine(Vector2f position, vector<double> sunshine_data, bool _type) {
    type = _type;
    rect.top = 0;
    rect.left = 0;
    rect.width = 117;
    rect.height = 116;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setPosition(position);
    set_data(sunshine_data);
}

void Sunshine::set_data(vector<double> sunshine_data){
    if(!texture.loadFromFile("assets/some picture/sun.png")) {
        exit(0);
    }
    sprite.setScale(1.2, 1.2);
    speed = sunshine_data[0];
    interval = sunshine_data[1];
}

void Sunshine::update() {
    if(type)
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

bool Sunshine::is_out(unsigned screen_height) {
    if(sprite.getPosition().y >= screen_height)
        return true;
    return false;
}

Sunshine::~Sunshine() {}