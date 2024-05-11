#pragma once
#include "require.hpp"
#include "plant.hpp"
// #include "bullet.hpp"

class AttackingPlant : public Plant {
public:
    AttackingPlant(int type);
    void build_animation();
    Bullet* shoot();

private:
    void store_textures();
    vector<Texture> textures;
    int number_of_idle_frames;
    int health;
    int damage;
    int cooldown;
    int hit_rate;
    int speed;
    int price;
    float speed_effect;

};