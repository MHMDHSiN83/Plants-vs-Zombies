
#include "../include/zombie.hpp"

Zombie::Zombie(int _type, Vector2f position, vector<double> regular_zombie, vector<double> zombies_attacking_data, int _height) {
    rect.top = 0;
    rect.left = 0;
    
    type = _type;
    if(type == 0){
        set_data_of_normal_zombie(regular_zombie, zombies_attacking_data, _height);
        store_textures_of_normal_zombie();
        sprite.setScale(0.5, 0.5);
        sprite.setTexture(texture);
        sprite.setTextureRect(rect);
        sprite.setPosition(position.x,  position.y - sprite.getGlobalBounds().height / 2);

    }
    else {
        set_data_of_giant_zombie(regular_zombie, zombies_attacking_data, _height);
        store_textures_of_giant_zombie();
        sprite.setScale(0.7, 0.7);
        sprite.setTexture(texture);
        sprite.setTextureRect(rect);
        sprite.setPosition(position.x, position.y - 2 * sprite.getGlobalBounds().height / 3);

    }
}

void Zombie::set_data_of_normal_zombie(vector<double> regular_zombie, vector<double> zombies_attacking_data, int _height){
    if(!texture.loadFromFile("assets/some picture/Zombie_healthy.png")) {
        exit(0);
    }
    rect.width = 335;
    rect.height = 745;
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

void Zombie::set_data_of_giant_zombie(vector<double> regular_zombie, vector<double> zombies_attacking_data, int _height){
    if(!texture.loadFromFile("assets/QQ/1.png")) {
        exit(0);
    }
    rect.width = 514;
    rect.height = 485;
    damage = regular_zombie[4];
    health = regular_zombie[5];
    hit_rate = regular_zombie[6];
    speed = regular_zombie[7];
    time_to_finish = zombies_attacking_data[0];
    new_mode = zombies_attacking_data[1];
    number_of_zombie = zombies_attacking_data[2];
    number_of_add_zombie = zombies_attacking_data[3];
    height = _height;
}

void Zombie::update() {
    if(!eating) {
        sprite.setPosition(sprite.getPosition().x - speed, sprite.getPosition().y);
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
        sprite.setTexture(textures[counter - 1]);
        if(timer_normal_zombie == 156) timer_normal_zombie = 0;
    }
    else {
     //   sprite.setScale(1, 1);
        timer_eating_normal_zombie++;
        int counter = ((timer_eating_normal_zombie/5 + 1) % NUMBER_OF_EATING_FRAMES_NORMAL_ZOMBIE )+ 1;
        sprite.setTexture(textures2[counter - 1]);
        if(timer_eating_normal_zombie == 61) timer_eating_normal_zombie = 0;
    }
}

void Zombie::build_animation_of_giant_zombie() {
    if(!eating){
        timer_giant_zombie++;
        int counter = ((timer_giant_zombie/5 + 1) % NUMBER_OF_IDLE_FRAMES_GIANT_ZOMBIE )+ 1;
        sprite.setTexture(textures_of_giant[counter - 1]);
        if(timer_giant_zombie == 306) timer_giant_zombie = 0;
    }
    else {
        //sprite.setScale(0.7, 0.7);
        timer_eating_giant_zombie++;
        int counter = ((timer_eating_giant_zombie/5 + 1) % NUMBER_OF_EATING_FRAMES_GIANT_ZOMBIE )+ 1;
        sprite.setTexture(textures_of_eating_giant[counter - 1]);
        if(timer_eating_giant_zombie == 146) timer_eating_giant_zombie = 0;
    }
}

void Zombie::store_textures_of_normal_zombie() {
    for (int i = 1; i <= NUMBER_OF_IDLE_FRAMES_NORMAL_ZOMBIE; i++)
    {
        Texture new_texture;
        new_texture.loadFromFile("assets/zom/" + to_string(i) + ".png");
        textures.push_back(new_texture);
    }
    for (int i = 1; i <= NUMBER_OF_EATING_FRAMES_NORMAL_ZOMBIE; i++)
    {
        Texture new_texture;
        new_texture.loadFromFile("assets/zom/eating/" + to_string(i) + ".png");
        textures2.push_back(new_texture);
    }
}

void Zombie::store_textures_of_giant_zombie() {
    for (int i = 1; i <= NUMBER_OF_IDLE_FRAMES_GIANT_ZOMBIE; i++)
    {
        Texture new_texture;
        new_texture.loadFromFile("assets/QQ/" + to_string(i) + ".png");
        textures_of_giant.push_back(new_texture);
    }
    for (int i = 1; i <= NUMBER_OF_EATING_FRAMES_GIANT_ZOMBIE; i++)
    {
        Texture new_texture;
        new_texture.loadFromFile("assets/QQQ/" + to_string(i) + ".png");
        textures_of_eating_giant.push_back(new_texture);
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