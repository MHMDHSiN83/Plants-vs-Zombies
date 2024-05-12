
#include "../include/zombie.hpp"

Zombie::Zombie(Vector2f position, int _height) {
    // if(!texture.loadFromFile("assets/some picture/Zombie_healthy.png")) {
    //     exit(0);
    // }
        if(!texture.loadFromFile("assets/pea.png")) {
        exit(0);
    }
    rect.top = 0;
    rect.left = 0;
    rect.width = 335;
    rect.height = 745;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setScale(0.6, 0.6);
    sprite.setPosition(position.x, MIN_HEIGHT + position.y - sprite.getGlobalBounds().height + 80);
    store_textures();
    health = 5;
    damage = 1;
    height = _height;
    hit_rate = 1;
}


void Zombie::update() {
    if(!eating)
        sprite.setPosition(sprite.getPosition().x - speed, sprite.getPosition().y);
}

void Zombie::render(RenderWindow* window) {
    window->draw(sprite);
}

void Zombie::build_animation() {
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

FloatRect Zombie::get_rect() { 
    FloatRect float_rect = sprite.getGlobalBounds();
    float_rect.left += sprite.getGlobalBounds().width/2;
    return float_rect;
}

int Zombie::get_height() { return height; }

void Zombie::decrease_health(int bullet_damage) { health -= bullet_damage; }

bool Zombie::is_dead() {
    if(health <= 0)
        return true;
    return false;
}


void Zombie::change_eating_situation() { eating = !eating; }

int Zombie::get_damage() { return damage; }
bool Zombie::is_eating() { return eating; }

int Zombie::get_hit_rate() { return hit_rate; }
Time Zombie::get_elapsed() { return hit_clock.getElapsedTime(); }
void Zombie::restart_clock() {  hit_clock.restart(); }