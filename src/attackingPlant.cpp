#include "../include/attackingPlant.hpp"


AttackingPlant::AttackingPlant(int _type) : Plant(_type) {
    if(type == 0) {
        number_of_idle_frames = 20;
        if(!texture.loadFromFile("assets/peashooter/peashooters/1.png")) {
            exit(0);
        }
        speed_effect = 1;
        health = 5;
        damage = 1;
        cooldown = 2;
        hit_rate = 1;
        speed = 2;
        price = 100;
    } else { 
        number_of_idle_frames = 18;
        if(!texture.loadFromFile("assets/Icepeoshooter/Icepeoshooter/1.png")) {
            exit(0);
        }
        speed_effect = 0.5;
        health = 5;
        damage = 1;
        cooldown = 3;
        hit_rate = 1;
        speed = 2;
        price = 175;
    }
    store_textures();
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
    if(elapsed.asSeconds() > 3) {
        action_clock.restart();
        return (new Bullet({sprite.getPosition().x + 2 * sprite.getGlobalBounds().width/3, sprite.getPosition().y + 30}, type));
    }
    return NULL;
}