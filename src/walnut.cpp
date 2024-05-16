#include "../include/walnut.hpp"


Walnut::Walnut(int _type, vector<double> walnut_data) : Plant(_type) {
    store_textures();
    set_data_of_walnut(walnut_data);
}

void Walnut::set_data_of_walnut(vector<double> walnut_data){
    sprite.setTexture(textures[0]);
    damage = walnut_data[0];
    health = walnut_data[1];
    cooldown = walnut_data[2];
    hit_rate = walnut_data[3];
    speed = walnut_data[4];
    price = walnut_data[5];
}

void Walnut::build_animation() {
    if(!is_planted) return;
    timer++;
    int counter = ((timer/5 + 1) % number_of_idle_frames )+ 1;
    sprite.setTexture(textures[counter - 1]);
    if(timer == 126) timer = 0;
}

void Walnut::store_textures() {
    for (int i = 1; i <= number_of_idle_frames; i++)
    {
        Texture new_texture;
        new_texture.loadFromFile(WALNUT_PATH + to_string(i) + ".png");
        textures.push_back(new_texture);
    }
}

void Walnut::decrease_health(double zombie_damage) { health -= zombie_damage; }

bool Walnut::is_dead() {
    if(health <= 0)
        return true;
    return false;
}