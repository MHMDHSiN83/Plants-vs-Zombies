#include "../include/attackingPlant.hpp"


AttackingPlant::AttackingPlant(int _type, vector<double> peashooter_data, vector<double> icepeashooter_data) : Plant(_type) {
    if(type == 0)
        set_data_of_peashooter(peashooter_data);
    else
        set_data_of_icepeashooter(icepeashooter_data);
    store_textures();
}

void AttackingPlant::set_data_of_peashooter(vector<double> peashooter_data){
    number_of_idle_frames = 20;
    if(!texture.loadFromFile("assets/peashooter/peashooters/1.png"))
        exit(0);
    speed_effect = 1;
    damage = peashooter_data[0];
    health = peashooter_data[1];
    cooldown = peashooter_data[2];
    hit_rate = peashooter_data[3];
    speed = peashooter_data[4];
    price = peashooter_data[5];
}

void AttackingPlant::set_data_of_icepeashooter(vector<double> icepeashooter_data){
    number_of_idle_frames = 18;
    if(!texture.loadFromFile("assets/Icepeoshooter/Icepeoshooter/1.png"))
        exit(0);
    speed_effect = 0.5;
    damage = icepeashooter_data[0];
    health = icepeashooter_data[1];
    cooldown = icepeashooter_data[2];
    hit_rate = icepeashooter_data[3];
    speed = icepeashooter_data[4];
    price = icepeashooter_data[5];
}

void AttackingPlant::build_animation() {
    if(!is_planted) return;
    timer++;
    int counter = ((timer/5 + 1) % number_of_idle_frames )+ 1;
    sprite.setTexture(textures[counter - 1]);
    if(timer == 101) timer = 0;
}

void AttackingPlant::store_textures() {
    for (int i = 1; i <= number_of_idle_frames; i++)
    {
        Texture new_texture;
        if(type == 0)
            new_texture.loadFromFile("assets/peashooter/peashooters/" + to_string(i) + ".png");
        else
            new_texture.loadFromFile("assets/Icepeoshooter/Icepeoshooter/" + to_string(i) + ".png");
        textures.push_back(new_texture);
    }
}

Bullet* AttackingPlant::shoot() {
    if(!is_planted)
        return NULL;
    Time elapsed = action_clock.getElapsedTime();
    if(elapsed.asSeconds() > hit_rate) {
        action_clock.restart();
        return (new Bullet({sprite.getPosition().x + 2 * sprite.getGlobalBounds().width/3, sprite.getPosition().y + 30}, type, width, height, speed, damage));
    }
    return NULL;
}

void AttackingPlant::decrease_health(double zombie_damage) { health -= zombie_damage; }

bool AttackingPlant::is_dead() {
    if(health <= 0)
        return true;
    return false;
}