#include "../include/card.hpp"

Card::Card(Vector2i first_card_position, int distance) {
    first_card_position.y += distance * 70;
    if(!texture.loadFromFile("assets/some picture/peashooter_card.png")) {
        exit(0);
    }
    rect.top = 0;
    rect.left = 0;
    rect.width = 280;
    rect.height = 174;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    Vector2f pos(first_card_position.x, first_card_position.y);
    sprite.setPosition(pos);
    sprite.setScale(0.3,0.3);
    is_clicked = false;
}

Card::~Card() {

}


// void Card::update(){
//     rect
// }


void Card::render(RenderWindow* window) {
    window->draw(sprite);
}



void Card::handle_mouse_pressed(Vector2i mouse_position) {
    Vector2f position = sprite.getPosition();
    Vector2f sprite_size = {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height};
    if(!is_clicked) {
        if (mouse_position.x >= position.x && mouse_position.x <= position.x + sprite_size.x &&
            mouse_position.y >= position.y && mouse_position.y <= position.y + sprite_size.y) {
            is_clicked = true;
        }
    } else {
        
        is_clicked = false;
    }
}
