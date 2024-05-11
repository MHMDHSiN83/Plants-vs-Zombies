
#include "../include/zombie.hpp"

Zombie::Zombie(Vector2f position) {
    if(!texture.loadFromFile("assets/some picture/Zombie_healthy.png")) {
        exit(0);
    }
    rect.top = 0;
    rect.left = 0;
    rect.width = 335;
    rect.height = 745;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setScale(0.6, 0.6);
    sprite.setPosition(position.x, MIN_HEIGHT + position.y - sprite.getGlobalBounds().height + 40);
    store_textures();
}


void Zombie::update() {
    sprite.setPosition(sprite.getPosition().x - speed, sprite.getPosition().y);
}

void Zombie::render(RenderWindow* window) {
    window->draw(sprite);
}

void Zombie::build_animation() {
    //if(!is_planted) return;
    //Texture new_texture;
    //new_texture.loadFromFile("assets/sunflower/" + to_string(1) + ".png");
    
    timer++;
    int counter = ((timer/5 + 1) % number_of_idle_frames )+ 1;
    sprite.setTexture(textures[counter - 1]);
    if(timer == 156) timer = 0;
}

void Zombie::store_textures() {
    for (int i = 1; i <= number_of_idle_frames; i++)
    {
        Texture new_texture;
        new_texture.loadFromFile("assets/zom/" + to_string(i) + ".png");
        textures.push_back(new_texture);
    }
}