#include "../include/sunflower.hpp"


Sunflower::Sunflower(int _type, vector<double> sunflower_data) : Plant(_type) {
    store_textures();
    set_data_of_sunflower(sunflower_data);
}

void Sunflower::set_data_of_sunflower(vector<double> sunflower_data){
    sprite.setTexture(textures[0]);
    damage = sunflower_data[0];
    health = sunflower_data[1];
    cooldown = sunflower_data[2];
    hit_rate = sunflower_data[3];
    speed = sunflower_data[4];
    price = sunflower_data[5];
}

void Sunflower::build_animation() {
    if(!is_planted) return;
    timer++;
    int counter = ((timer/5 + 1) % number_of_idle_frames )+ 1;
    sprite.setTexture(textures[counter - 1]);
    if(timer == 156) timer = 0;
}

void Sunflower::store_textures() {
    for (int i = 1; i <= number_of_idle_frames; i++)
    {
        Texture new_texture;
        new_texture.loadFromFile(SUNFLOWER_PATH + to_string(i) + ".png");
        textures.push_back(new_texture);
    }
}

void Sunflower::decrease_health(double zombie_damage) { health -= zombie_damage; }

bool Sunflower::is_dead() {
    if(health <= 0)
        return true;
    return false;
}

bool Sunflower::is_time_to_create_sunshine() {
    if(!is_planted)
        return false;
    Time elapsed = create_sunshine.getElapsedTime();
    if(elapsed.asSeconds() > hit_rate) {
        create_sunshine.restart();
        return true;
    }
    return false;
}
