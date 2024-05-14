#include "../include/walnut.hpp"


Walnut::Walnut(int _type, vector<double> walnut_data) : Plant(_type) {
    store_textures();
    set_data_of_walnut(walnut_data);
    starting_health = health;
}

void Walnut::set_data_of_walnut(vector<double> walnut_data){
    if(!texture.loadFromFile("assets/walnut/1.png")) {
        exit(0);
    }
    damage = walnut_data[0];
    health = walnut_data[1];
    cooldown = walnut_data[2];
    hit_rate = walnut_data[3];
    speed = walnut_data[4];
    price = walnut_data[5];
}

void Walnut::build_animation() {
    if(!is_planted) return;
    if(set_picture() == 2){
        texture.loadFromFile("assets/walnut/A.png");
        rect.width = 100;
        rect.height = 100;
        rect.top = -20;
        rect.left = -20;
        sprite.setScale(1.15,1.15);
        sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y);
    sprite.setTextureRect(rect);

        sprite.setTexture(texture);
        return;
    }
    if(set_picture() == 1){
        texture.loadFromFile("assets/walnut/B.png");
        rect.width = 100;
        rect.height = 100;
        rect.top = -20;
        rect.left = -20;
        sprite.setScale(1.15,1.15);
        sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y);
        
    sprite.setTextureRect(rect);
    sprite.setTexture(texture);
    return;
    }
    timer++;
    int counter = ((timer/5 + 1) % number_of_idle_frames )+ 1;
    sprite.setTexture(textures[counter - 1]);
    if(timer == 126) timer = 0;
}

void Walnut::store_textures() {
    little_scar.loadFromFile("assets/walnut/A.png");
    big_scar.loadFromFile("assets/walnut/B.png");
    for (int i = 1; i <= number_of_idle_frames; i++)
    {
        Texture new_texture;
        new_texture.loadFromFile("assets/walnut/" + to_string(i) + ".png");
        textures.push_back(new_texture);
    }
}

void Walnut::decrease_health(double zombie_damage) { health -= zombie_damage; }

bool Walnut::is_dead() {
    if(health <= 0)
        return true;
    return false;
}

int Walnut::set_picture(){
    if(health < (starting_health / 3)){
        return 1;
    }
    if(health < (starting_health / 3) * 2){ 
        return 2;
    }
    return 0;
}