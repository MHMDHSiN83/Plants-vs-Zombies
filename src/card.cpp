#include "../include/card.hpp"
// #include "../include/plant.hpp"
Card::Card(Vector2i first_card_position, int _type) {
    type = _type;
    set_texture();
    rect.top = 0;
    rect.left = 0;
    rect.width = 188;//280
    rect.height = 112;//174
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    first_card_position.y += _type * 140;
    Vector2f pos(first_card_position.x, first_card_position.y);
    sprite.setPosition(pos);
    sprite.setScale(1,1);// 0.6 0.6
    is_clicked = false;
    timer = 0;
}

void Card::set_texture() {
    switch (type)
    {
    case 0:
        if(!texture.loadFromFile("assets/cards/on_peashooter.png"))
            exit(0);
        if(!pressed_texture.loadFromFile("assets/cards/off_peashooter.png"))
            exit(0);
        break;
    case 1:
        if(!texture.loadFromFile("assets/cards/on_sunflower.png"))
            exit(0);
        if(!pressed_texture.loadFromFile("assets/cards/off_sunflower.png"))
            exit(0);
        break;
    case 2:
        if(!texture.loadFromFile("assets/cards/on_wallnut.png"))
            exit(0);
        if(!pressed_texture.loadFromFile("assets/cards/off_wallnut.png"))
            exit(0);
        break;
    case 3:
        if(!texture.loadFromFile("assets/cards/on_snow_peashooter.png"))
            exit(0);
        if(!pressed_texture.loadFromFile("assets/cards/off_snow_peashooter.png"))
            exit(0);
        break;
    }
}

Card::~Card() {

}


void Card::update(){
    if(is_clicked) {
        Time elapsed = clock.getElapsedTime();
        if(elapsed.asSeconds() > 2) {
            sprite.setTexture(texture);
            is_clicked = false;
            clock.restart();
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
            return true;
        }
    }
    return false;
}

void Card::reset_card() { 
    is_clicked = false;
    sprite.setTexture(texture);
}

void Card::start_timer() { 
    clock.restart();
    is_clicked = true;
}