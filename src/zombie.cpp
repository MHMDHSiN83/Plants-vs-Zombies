
#include "../include/zombie.hpp"

Zombie::Zombie(int _type, Vector2f position, vector<double> zombie_data, int _height) {
    rect.top = 0;
    rect.left = 0;
    type = _type;
    damage = zombie_data[0];
    health = zombie_data[1];
    hit_rate = zombie_data[2];
    starting_speed = zombie_data[3];
    height = _height;
    current_speed = starting_speed;
    if(type == 0)
        set_data_of_normal_zombie(position);
    else
        set_data_of_giant_zombie(position);
}

void Zombie::set_data_of_normal_zombie(Vector2f position){
    store_textures_of_normal_zombie();
    rect.width = 335;
    rect.height = 745;
    sprite.setScale(0.5, 0.5);
    sprite.setTexture(walking_textures[0]);
    sprite.setTextureRect(rect);
    sprite.setPosition(position.x,  position.y - sprite.getGlobalBounds().height / 2);
}

void Zombie::set_data_of_giant_zombie(Vector2f position){
    store_textures_of_giant_zombie();
    rect.width = 514;
    rect.height = 485;
    sprite.setScale(0.7, 0.7);
    sprite.setTexture(walking_textures[0]);
    sprite.setTextureRect(rect);
    sprite.setPosition(position.x, position.y - 2 * sprite.getGlobalBounds().height / 3);
}

void Zombie::update() {
    if(!eating) {
        sprite.setPosition(sprite.getPosition().x - current_speed, sprite.getPosition().y);
    }
    if(current_speed != starting_speed) {
        Time elapsed = freeze_clock.getElapsedTime();
        if(elapsed.asSeconds() > FREEZE_TIME) {
            current_speed = starting_speed;
        }
    }
}

void Zombie::render(RenderWindow* window) {
    window->draw(sprite);
}
void Zombie::build_animation() {
    if(type == 0) {
        build_animation_of_normal_zombie();
    } else {
        build_animation_of_giant_zombie();
    }
}

void Zombie::build_animation_of_normal_zombie() {
    if(!eating){
        timer_normal_zombie++;
        int counter = ((timer_normal_zombie/5 + 1) % NUMBER_OF_IDLE_FRAMES_NORMAL_ZOMBIE )+ 1;
        sprite.setTexture(walking_textures[counter - 1]);
        if(timer_normal_zombie == 156) timer_normal_zombie = 0;
    }
    else {
        timer_eating_normal_zombie++;
        int counter = ((timer_eating_normal_zombie/5 + 1) % NUMBER_OF_EATING_FRAMES_NORMAL_ZOMBIE )+ 1;
        sprite.setTexture(eating_textures[counter - 1]);
        if(timer_eating_normal_zombie == 61) timer_eating_normal_zombie = 0;
    }
}

void Zombie::build_animation_of_giant_zombie() {
    if(!eating){
        timer_giant_zombie++;
        int counter = ((timer_giant_zombie/5 + 1) % NUMBER_OF_IDLE_FRAMES_GIANT_ZOMBIE )+ 1;
        sprite.setTexture(walking_textures[counter - 1]);
        if(timer_giant_zombie == 306) timer_giant_zombie = 0;
    }
    else {
        sprite.getPosition();
        timer_eating_giant_zombie++;
        int counter = ((timer_eating_giant_zombie/5 + 1) % NUMBER_OF_EATING_FRAMES_GIANT_ZOMBIE )+ 1;
        sprite.setTexture(eating_textures[counter - 1]);
        if(timer_eating_giant_zombie == 146) timer_eating_giant_zombie = 0;
    }
}

void Zombie::store_textures_of_normal_zombie() {
    for (int i = 1; i <= NUMBER_OF_IDLE_FRAMES_NORMAL_ZOMBIE; i++)
    {
        Texture new_texture;
        new_texture.loadFromFile(REGULAR_WALKING_ZOMBIE_PATH + to_string(i) + ".png");
        walking_textures.push_back(new_texture);
    }
    for (int i = 1; i <= NUMBER_OF_EATING_FRAMES_NORMAL_ZOMBIE; i++)
    {
        Texture new_texture;
        new_texture.loadFromFile(REGULAR_EATING_ZOMBIE_PATH + to_string(i) + ".png");
        eating_textures.push_back(new_texture);
    }
}

void Zombie::store_textures_of_giant_zombie() {
    for (int i = 1; i <= NUMBER_OF_IDLE_FRAMES_GIANT_ZOMBIE; i++)
    {
        Texture new_texture;
        new_texture.loadFromFile(GIANT_WALKING_ZOMBIE_PATH + to_string(i) + ".png");
        walking_textures.push_back(new_texture);
    }
    for (int i = 1; i <= NUMBER_OF_EATING_FRAMES_GIANT_ZOMBIE; i++)
    {
        Texture new_texture;
        new_texture.loadFromFile(GIANT_EATING_ZOMBIE_PATH + to_string(i) + ".png");
        eating_textures.push_back(new_texture);
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

void Zombie::speed_effect(double speed_effect) {
    if(speed_effect != 1) {
        current_speed = starting_speed * speed_effect;
        freeze_clock.restart();
    }
}

Zombie::~Zombie() {}