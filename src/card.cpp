#include "../include/card.hpp"
// #include "../include/plant.hpp"
Card::Card(Vector2i first_card_position, int _type) {
    type = _type;
    set_texture();
    rect.top = 0;
    rect.left = 0;
    rect.width = 280;
    rect.height = 174;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    first_card_position.y += _type * 140;
    Vector2f pos(first_card_position.x, first_card_position.y);
    sprite.setPosition(pos);
    sprite.setScale(0.6,0.6);
    is_clicked = false;
    timer = 0;
}

void Card::set_texture() {
    switch (type)
    {
    case 0:
        if(!texture.loadFromFile("assets/some picture/peashooter_card.png"))
            exit(0);
        if(!pressed_texture.loadFromFile("assets/some picture/peashooter_pressed.png"))
            exit(0);
        break;
    case 1:
        if(!texture.loadFromFile("assets/some picture/sunflower_card.png"))
            exit(0);
        if(!pressed_texture.loadFromFile("assets/some picture/sunflower_pressed.png"))
            exit(0);
        break;
    case 2:
        if(!texture.loadFromFile("assets/some picture/walnut_card.png"))
            exit(0);
        if(!pressed_texture.loadFromFile("assets/some picture/walnut_pressed.png"))
            exit(0);
        break;
    }
}

Card::~Card() {

}


void Card::update(){
    if(is_clicked) {
        system_clock::time_point now = system_clock::now();
        duration<double> distance = now - last_time_clicked;
        if(distance.count() > SUNSHINE_TIMER) {
            sprite.setTexture(texture);
            is_clicked = false;
        }
    }
}


void Card::render(RenderWindow* window) {
    window->draw(sprite);
}

bool Card::handle_mouse_pressed(Vector2i mouse_position) {
    Vector2f position = sprite.getPosition();
    Vector2f sprite_size = {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height};
    if(!is_clicked) {
        if (mouse_position.x >= position.x && mouse_position.x <= position.x + sprite_size.x &&
            mouse_position.y >= position.y && mouse_position.y <= position.y + sprite_size.y) {
            sprite.setTexture(pressed_texture);
            last_time_clicked = system_clock::now();
            is_clicked = true;
            return true;
        }
    }
    return false;
}

void Card::reset_card() { 
    is_clicked = false;
    sprite.setTexture(texture);
}