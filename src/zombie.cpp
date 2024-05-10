
#include "../include/zombie.hpp"

Zombie::Zombie(Vector2f position) {
    if(!texture.loadFromFile("assets/some picture/Zombie_healthy.png")) {
        exit(0);
    }
    rect.top = 0;
    rect.left = 0;
    rect.width = 291;
    rect.height = 465;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setScale(0.5, 0.5);
    sprite.setPosition(position.x, position.y - sprite.getGlobalBounds().height + 40);
}


void Zombie::update() {
    sprite.setPosition(sprite.getPosition().x - speed, sprite.getPosition().y);
}

void Zombie::render(RenderWindow* window) {
    window->draw(sprite);
}
