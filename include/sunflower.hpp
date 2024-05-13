#pragma once
#include "require.hpp"
#include "plant.hpp"

class Sunflower : public Plant {
public:
    Sunflower(int type, vector<double> sunflower_data);
    void build_animation();
private:
    void store_textures();
    vector<Texture> textures;
    int number_of_idle_frames = 31;
    double damage;
    double health;
    double cooldown;
    double hit_rate;
    double speed;
    double price;
    void set_data_of_sunflower(vector<double> sunflower_data);
};