
#include "../include/zombie.hpp"

Zombie::Zombie(Vector2f position, vector<double> regular_zombie, vector<double> zombies_attacking_data, int _height) {
    rect.top = 0;
    rect.left = 0;
    rect.width = 335;
    rect.height = 745;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setScale(0.6, 0.6);
    sprite.setPosition(position.x, MIN_HEIGHT + position.y - sprite.getGlobalBounds().height + 80);
    store_textures();
    set_data(regular_zombie, zombies_attacking_data, _height);
}

void Zombie::set_data(vector<double> regular_zombie, vector<double> zombies_attacking_data, int _height){
    if(!texture.loadFromFile("assets/some picture/Zombie_healthy.png")) {
        exit(0);
    }
    damage = regular_zombie[0];
    health = regular_zombie[1];
    hit_rate = regular_zombie[2];
    speed = regular_zombie[3];
    time_to_finish = zombies_attacking_data[0];
    new_mode = zombies_attacking_data[1];
    number_of_zombie = zombies_attacking_data[2];
    number_of_add_zombie = zombies_attacking_data[3];
    height = _height;
}

void Zombie::update() {
    if(!eating)
        sprite.setPosition(sprite.getPosition().x - speed, sprite.getPosition().y);
}

void Zombie::render(RenderWindow* window) {
    window->draw(sprite);
}

void Zombie::build_animation() {
    if(!eating){
        timer++;
        int counter = ((timer/5 + 1) % number_of_idle_frames )+ 1;
        sprite.setTexture(textures[counter - 1]);
        if(timer == 156) timer = 0;
    }
    else {
        timer2++;
        int counter = ((timer2/5 + 1) % number_of_idle_frames2 )+ 1;
        sprite.setTexture(textures2[counter - 1]);
        if(timer2 == 61) timer2 = 0;
    }
}

void Zombie::store_textures() {
    for (int i = 1; i <= number_of_idle_frames; i++)
    {
        Texture new_texture;
        new_texture.loadFromFile("assets/zom/" + to_string(i) + ".png");
        textures.push_back(new_texture);
    }
    for (int i = 1; i <= number_of_idle_frames2; i++)
    {
        Texture new_texture;
        new_texture.loadFromFile("assets/zom/eating/" + to_string(i) + ".png");
        textures2.push_back(new_texture);
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

double Zombie::get_damage() { return damage; }
bool Zombie::is_eating() { return eating; }

double Zombie::get_hit_rate() { return hit_rate; }
Time Zombie::get_elapsed() { return hit_clock.getElapsedTime(); }
void Zombie::restart_clock() {  hit_clock.restart(); }

bool Zombie::is_out() {
    if(sprite.getPosition().x < 0)
        return true;
    return false;
}