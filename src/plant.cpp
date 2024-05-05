#include "../include/plant.hpp"



Plant::Plant() {

    if(!texture.loadFromFile("assets/peashooter.png")) {
        exit(0);
    }
    rect.top = 0;
    rect.left = 0;
    rect.width = 50;
    rect.height = 50;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    Vector2f pos(100.f, 100.f);
    sprite.setPosition(pos);
}

Plant::~Plant() {

}

void Plant::update() {

}

void Plant::render(RenderWindow* window) {
    window->draw(sprite);
}
