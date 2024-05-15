#pragma once
#include "require.hpp"
#include "plant.hpp"

class Peashooter : public Plant {
public:
    Peashooter(int type);
    void build_animation();
private:
    void store_textures();
    vector<Texture> textures;
    int number_of_idle_frames = 20;
    int health;
    int damage;
    int cooldown;
    int hit_rate;
    int speed;
    int price;
};